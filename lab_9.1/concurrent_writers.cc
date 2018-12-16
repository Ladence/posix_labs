#include <array>
#include <atomic>
#include <fstream>
#include <iostream>
#include <mutex>
#include <string>
#include <cstring>
#include <vector>

#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

class writer {
private:
	static constexpr size_t MAP_SIZE = 0x1000;
	static constexpr key_t SHM_KEY = 0x36000;

	struct {
		std::atomic_uint16_t current_writer_id;
		std::array<uint16_t, 3> writers_order;
		std::array<bool, 3> ready;
		std::array<bool, 3> done;
	}* shared_vars_;
	int32_t  shmid_;
	uint16_t id_;
	uint16_t order_index_;
	size_t lines_count_;
	std::ofstream out_file_;

	void open_shm_() {
		// connect to shared memory segment or create new one
		shmid_ = shmget(SHM_KEY, MAP_SIZE, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
		if (shmid_ == -1 && errno == EEXIST) {
			shmid_ = shmget(SHM_KEY, 0, 0);
		}
		if (shmid_ == -1) {
			throw std::runtime_error(strerror(errno));
		}
		// interpret pointer to shared memory as specified structure
		shared_vars_ = reinterpret_cast<decltype(shared_vars_)>(
			shmat(shmid_, nullptr, 0)
		);
	}

	void init_shared_vars_() {
		shared_vars_->writers_order[order_index_] = id_;
		shared_vars_->ready[id_] = true;
		shared_vars_->done[id_] = false;

		// all processes started
		if (shared_vars_->ready[0] && shared_vars_->ready[1] &&
			shared_vars_->ready[2]) {
			// check for uniqueness
			if (shared_vars_->writers_order[0] == shared_vars_->writers_order[1]
			|| shared_vars_->writers_order[0] == shared_vars_->writers_order[2]
			|| shared_vars_->writers_order[1] == shared_vars_->writers_order[2]) {
				throw std::runtime_error("invalid write order: duplicates detected");
			}
			// set first writer
			if (order_index_ == 0) {
				shared_vars_->current_writer_id = id_;
			} else {
				shared_vars_->current_writer_id = 3;
			}
		}
	}

	writer (char const* args[] = nullptr) {
		// open output file
		out_file_.open(args[1], std::ios::app);
		if (!out_file_.is_open()) {
			throw std::runtime_error("invalid output file");
		}
		std::cerr << "file opened\n";

		// obtain current id from last character in executable name
		id_ = std::stoi(std::string(args[0] + strlen(args[0]) - 1));
		std::cerr << id_ << " - writer id\n";
		// possible values: 0, 1, 2
		order_index_ = std::stoi(args[2]);
		std::cerr << order_index_ << " - order index\n";
		if (order_index_ > 2) {
			throw std::runtime_error("invalid order index value");
		}
		lines_count_ = std::stoi(args[3]);
		std::cerr << lines_count_ << " - lines count\n";

		open_shm_();
		std::cerr << shmid_ << "shared memory id\n";
		std::cerr << shared_vars_ << "shared memory address\n";
		init_shared_vars_();
	}

	~writer () {
		shmdt(shared_vars_);
		out_file_.close();
	}

public:
	static writer& instance(char const* args[] = nullptr) {
		static writer inst(args);
		return inst;
	}
	writer(writer const&) = delete;
	void operator=(writer const&) = delete;

	void write_lines() {
		while (lines_count_ > 0) {
			if (!shared_vars_->ready[0] || !shared_vars_->ready[1] ||
			!shared_vars_->ready[2]) {
				// std::cerr << "one of writerss isn't ready\n";
				continue;
			}
			// temporary storage for id_ field
			auto id = id_;
			// if it is this process's turn
			if (shared_vars_->current_writer_id.compare_exchange_strong(id, id_)) {
				lines_count_--;
				std::cerr << "start writing line\n";
				out_file_ << "writer with id: " << id_
				<< "; lines left: " << lines_count_ << std::endl;

				// writing done
				if (lines_count_ == 0) {
					shared_vars_->done[id_] = true;
					std::cerr << "done\n";
				}
				std::cerr << lines_count_ << " - lines left\n";

				// all done
				if (shared_vars_->done[0] && shared_vars_->done[1] &&
					shared_vars_->done[2]) {
					std::cerr << "all done\n";
					return;
				}

				// pass to next
				auto next_id = shared_vars_->writers_order[(order_index_ + 1) % 3];
				for (uint16_t i{2}; i <= 3 && shared_vars_->done[next_id]; i++) {
					next_id = shared_vars_->writers_order[(order_index_ + i) % 3];
				}
				std::cerr << next_id << " - next writer\n";
				shared_vars_->current_writer_id = next_id;
			}
		}
	}
};

int main(int argc, char const* argv[]) {
	if (argc < 4) {
		std::cerr << "usage: cncr_wrtr <output filename> <order index> <lines count>\n";
		return 0;
	}

	try {
		auto& writer_instance = writer::instance(argv);
		writer_instance.write_lines();
	} catch(std::runtime_error ex) {
		std::cerr << ex.what() << '\n';
	}

	std::cout << std::flush;
	std::cerr << std::flush;
	return 0;
}
