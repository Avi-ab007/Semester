#include <bits/stdc++.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <poll.h>
#include <sys/time.h>
using namespace std;
string pipes[] = {"/tmp/pipe1", "/tmp/pipe2", "/tmp/pipe3"};
string proc[] = {"./p1", "./p2", "./p3"};
struct pollfd pfd[3];

int main() {
	for (int i = 0; i < 3; i++) {
		mkfifo(pipes[i].c_str(), 0666);
		int pid = fork();
		if (pid > 0) {
			pfd[i].fd = open(pipes[i].c_str(), O_RDONLY);
			pfd[i].events = 0;
			pfd[i].events |= POLLIN;
		} else {

			execvp(proc[i].c_str(), NULL);
		}
	}

	while (true) {
		char buf[1000];
		for (int i = 0; i < 3; i++) {
			pfd[i].events = POLLIN;
		}
		poll(pfd, 3, 1);
		for (int i = 0; i < 3; i++) {
			if (pfd[i].revents & POLLIN) {
				if (read(pfd[i].fd, buf, 100)) {
					printf("Process %d sent data: %s\n", i+1, buf);
					break;
				}
			}
		}
	}

	for (int i = 0; i < 3; i++)
		close(pfd[i].fd);

	return 0;
}