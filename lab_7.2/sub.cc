#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

enum ARGS {
	FILENAME = 1,
	FD_READ = 2,
	FD_WRITE = 3,
	PARITY = 4};

constexpr uint8_t ODD = 1;
constexpr uint8_t EVEN = 2;

std::ofstream out_file;
int pipe_fd;
bool running = true;
uint8_t parity;

void sig_handler(int sig) {
	// invalid combinations of parity and sig
	if ((parity == ODD && sig == SIGUSR2) ||
		(parity == EVEN && sig == SIGUSR1)) {
		return;
	}

	// new symbol was requested
	char symbol{0};
	if (read(pipe_fd, &symbol, 1) > 0) {
		out_file << symbol;
		out_file << std::flush;
	} else {
		if (sig == SIGUSR1) {
			killpg(0, SIGUSR2);
		} else {
			killpg(0, SIGUSR1);
		}
		out_file.close();
		_exit(0);
	}

	if (sig == SIGUSR1) {
		killpg(0, SIGUSR2);
	} else {
		killpg(0, SIGUSR1);
	}
}

int main(int argc, char const *argv[]) {
	// open output file
	out_file.open(argv[FILENAME], std::ios::out);
	if (!out_file.is_open()) {
		std::cerr << "invalid output file name" << std::endl;
		_exit(1);
	}

	// obtain read end
	pipe_fd = std::stoi(argv[FD_READ]);
	auto write_end = std::stoi(argv[FD_WRITE]);
	close(write_end);

	// get parity
	parity = std::stoi(argv[PARITY]);

	// init sync loop
	struct sigaction psa;
	psa.sa_handler = sig_handler;
	sigaction(SIGUSR1, &psa, NULL);
	sigaction(SIGUSR2, &psa, NULL);

	// child ready to read
	kill(getppid(), SIGPOLL);

	// wait until parent reads file
	while (running);

	out_file.close();
	return 0;
}
