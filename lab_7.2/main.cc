#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

enum ARGS {
	INPUT = 1,
	OUTPUT_FIRST = 2,
	OUTPUT_SECOND = 3};

enum PIPE_FD {
	FD_READ,
	FD_WRITE};

pid_t odd_pid;
pid_t even_pid;

uint64_t file_size = 0;
bool child_ready = false;

int start_sub(const char* filename, int* pipe_fd) {
	static uint8_t parity = 0;
	parity++;
	pid_t current_pid = vfork();
	if (current_pid < 0) {
		// error handling
			std::cerr << "failed on vfork()" << std::endl;
		exit(1);
	} else if (current_pid == 0) {
		// execute subroutine
		int status = execl("./task_2_sub", "./task_2_sub", filename,
		std::to_string(pipe_fd[0]).c_str(), std::to_string(pipe_fd[1]).c_str(),
		std::to_string(parity).c_str(), nullptr);

		if (status == -1) {
			perror("subroutine execution error");
			_exit(1);
		}
	} else {
		return current_pid;
	}
}

void sig_handler(int sig) {
	if (sig == SIGPOLL) {
		child_ready = true;
		return;
	}
}

int main(int argc, char const *argv[]) {
	// check args
	if (argc < 4) {
		std::cerr << "usage: task_2_main <in file> <out file> <out file>" << '\n';
		return 0;
	}

	// open input file
	std::ifstream in_file(argv[INPUT], std::ios::in);
	if (!in_file.is_open()) {
		std::cerr << "invalid input file name" << std::endl;
		exit(1);
	}

	// open pipe
	int pipe_fd[2];
	if (pipe(pipe_fd) == -1) {
		perror("openning pipe errro");
		exit(1);
	}

	// init sync loop
	struct sigaction psa;
	psa.sa_handler = sig_handler;
	sigaction(SIGUSR1, &psa, NULL);
	sigaction(SIGUSR2, &psa, NULL);
	sigaction(SIGPOLL, &psa, NULL);

	// make two subroutines and wait until them sets signal handler
	odd_pid = start_sub(argv[OUTPUT_FIRST], pipe_fd);
	while (!child_ready);
	child_ready = false;
	even_pid = start_sub(argv[OUTPUT_SECOND], pipe_fd);
	while (!child_ready);

	// start syncing
	kill(odd_pid, SIGUSR1);

	// close unused read end
	close(pipe_fd[FD_READ]);

	// transmit by line
	std::string line;
	while (std::getline(in_file, line)) {
		line.push_back('\n');
		file_size += line.length();
		if (write(pipe_fd[FD_WRITE], line.data(), line.length()) == -1) {
			perror("writing in pipe error");
		}
	}

	// reading finished
	close(pipe_fd[FD_WRITE]);
	in_file.close();

	while (waitpid(-1, nullptr, 0) != -1);
	return 0;
}
