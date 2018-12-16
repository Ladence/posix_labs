#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>

#include <signal.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

class reader {
private:
	// messages for communicate with other reader
	#pragma pack(push, 1)
	struct message {
		union {
			// unique type
			int64_t mtype;
			struct {
				// who send
				int16_t transmitter;
				// who should receive
				int16_t receiver;
				// response or request
				int32_t direction;
			};
		};
		// when message was send
		time_t stamp;
		// id of messages queue
		int32_t msqid;
	};
	#pragma pack(pop)

	static constexpr size_t MSG_SIZE = sizeof(message::stamp) +
	sizeof(message::mtype);
	static constexpr key_t MSG_QUEUE_KEY = 0xdead;
	static constexpr int32_t MSG_REQUEST = 0;
	static constexpr int32_t MSG_RESPONSE = 1;

	static int32_t msqid_;
	std::array<int16_t, 3> rdrs_id_;
	std::array<message, 2> confirms_;
	std::array<bool, 2> serve_later_;
	bool is_confirmed_;
	std::ifstream in_file_;
	time_t own_rqst_time_;
	static struct sigaction sa_;

	void open_msg_queue_() {
		// connect to messages queue or create new one
		msqid_ = msgget(MSG_QUEUE_KEY, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
		if (msqid_ == -1 && errno == EEXIST) {
			msqid_ = msgget(MSG_QUEUE_KEY, 0);
		}
		if (msqid_ == -1) {
			throw std::runtime_error(strerror(errno));
		}
	}

	void set_rdrs_id_(std::string execname) {
		// obtain current id from last character in executable name
		std::string last{execname.end() - 1, execname.end()};
		auto cur_id = std::stoi(last);
		// current should be first
		std::swap(rdrs_id_[0], rdrs_id_[cur_id]);
	}

	static void sigint_handler_(int sig) {
		msgctl(msqid_, IPC_RMID, nullptr);
		std::cerr << "messages queue removed\n";
		exit(1);
	}

	message make_msg_(int16_t receiver, int32_t direction) {
		message msg;
		msg.direction = direction;
		msg.receiver = receiver;
		msg.transmitter = rdrs_id_[0];
		msg.stamp = own_rqst_time_;
		msg.msqid = msqid_;
		return msg;
	}

	message make_request_(int16_t receiver) {
		return make_msg_(receiver, MSG_REQUEST);
	}

	message make_confirm_(int16_t receiver) {
		return make_msg_(receiver, MSG_RESPONSE);
	}

	void request_reading_() {
		std::cerr << "request time: " << ctime(&own_rqst_time_) << "\n";

		for (size_t i{1}; i < 3; i++) {
			std::cerr << "send request for: " << rdrs_id_[i] << "\n";
			auto request = make_request_(rdrs_id_[i]);
			if (msgsnd(msqid_, &request, MSG_SIZE, 0) == -1) {
				throw std::runtime_error(strerror(errno));
			}
		}
	}

	int64_t type_(int16_t transmitter, int32_t direction) {
		message msg;
		msg.direction = direction;
		msg.transmitter = transmitter;
		msg.receiver = rdrs_id_[0];
		return msg.mtype;
	}

	int64_t request_type_(int16_t transmitter) {
		return type_(transmitter, MSG_REQUEST);
	}

	int64_t confirm_type_(int16_t transmitter) {
		return type_(transmitter, MSG_RESPONSE);
	}

	void send_confirm_(int16_t receiver) {
		std::cerr << "send confirm to: " << receiver << "\n";
		auto confirm = make_confirm_(receiver);
		if (msgsnd(msqid_, &confirm, MSG_SIZE, 0) == -1) {
			throw std::runtime_error(strerror(errno));
		}
	}

	reader(char const* args[] = nullptr)
	: rdrs_id_{0, 1, 2}, serve_later_{false, false}, is_confirmed_{false} {
		// should handle ctrl+c
		sa_.sa_handler = sigint_handler_;
		// open input file
		in_file_.open(args[1], std::ios::in);
		if (!in_file_.is_open()) {
			throw std::runtime_error("invalid input file");
		}
		std::cerr << "file opened\n";
		open_msg_queue_();
		std::cerr << "message queue id: " << msqid_ <<  "\n";
		set_rdrs_id_(args[0]);
		std::cerr << "readers id: " << rdrs_id_[0] << rdrs_id_[1] << rdrs_id_[2] << "\n";
		own_rqst_time_ = time(nullptr);
		request_reading_();
		std::cerr << "requests sended\n";
	}
public:
	static reader& instance(char const* args[] = nullptr) {
		static reader inst(args);
		return inst;
	}
	reader(reader const&) = delete;
  	void operator=(reader const&) = delete;

	// return true if two confirms sended
	bool serve_requests() {
		// should send only two confirms
		static bool served[] = {false, false};
		if (served[0] && served[1]) {
			return true;
		}

		// check both readers
		for (size_t i{1}; i < 3; i++) {
			if (served[i - 1]) {
				continue;
			}
			if (serve_later_[i - 1] && is_confirmed_) {
				send_confirm_(rdrs_id_[i]);
				served[i - 1] = true;
				continue;
			}

			std::cerr << "receive request from: " << rdrs_id_[i] << "\n";
			message request{0};
			// receive request
			if (msgrcv(msqid_, &request, MSG_SIZE, request_type_(rdrs_id_[i]),
			IPC_NOWAIT) == -1) {
				// no messages, it's okay
				if (errno == ENOMSG) {
					std::cerr << "no messages\n";
					continue;
				} else {
					throw std::runtime_error(strerror(errno));
				}
			}
			// received request is later than own
			if (request.stamp > own_rqst_time_) {
				std::cerr << "received stamp > own\n";
				serve_later_[i - 1] = true;
			} else {
				send_confirm_(rdrs_id_[i]);
				served[i - 1] = true;
			}
		}

		return served[0] && served[1];
	}

	uint8_t seek_confirms() {
		// requires two confirms
		static uint8_t confirms_count{0};
		if (confirms_count == 2) {
			return confirms_count;
		}

		// each reader should send confirm
		for (size_t i{1}; i < 3; i++) {
			std::cerr << "receive confirm from: " << rdrs_id_[i] << "\n";
			if (msgrcv(msqid_, &confirms_[i - 1], MSG_SIZE,
			confirm_type_(rdrs_id_[i]), IPC_NOWAIT) == -1) {
				// no messages, it's okay
				if (errno == ENOMSG) {
					std::cerr << "no messages\n";
					continue;
				} else {
					throw std::runtime_error(strerror(errno));
				}
			}

			std::cerr << "confirmed from: " << rdrs_id_[i] << "\n";
			confirms_count++;
		}
		if (confirms_count == 2) {
			is_confirmed_ = true;
		}
		return confirms_count;
	}

	void print_confirms() {
		std::cout << "this id: " << rdrs_id_[0]
		<< "\this time stamp: " << ctime(&own_rqst_time_) << std::endl;

		for (auto& confirm : confirms_) {
			std::cout << "confirm from: " << confirm.transmitter
			<< " at: " << ctime(&confirm.stamp) << std::endl;
		}
	}

	void print_file() {
		std::string line;
		while (std::getline(in_file_, line)) {
			std::cout << line << '\n';
		}
	}

	~reader() {
		in_file_.close();
	}
};
int32_t reader::msqid_{};
struct sigaction reader::sa_{};
int main(int argc, char const *argv[]) {
	// check args
	if (argc < 2) {
		std::cerr << "usage: cncr_rdr <filename>\n";
		return 0;
	}

	try {
		auto& reader_instance = reader::instance(argv);

		while (reader_instance.seek_confirms() < 2) {
			reader_instance.serve_requests();
			usleep(10);
		}

		reader_instance.print_confirms();
		reader_instance.print_file();

		while (!reader_instance.serve_requests());
	} catch(std::runtime_error ex) {
		std::cerr << ex.what() << '\n';
	}

	std::cout << std::flush;
	std::cerr << std::flush;
	std::cin.get();
	return 0;
}
