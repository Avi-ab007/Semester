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

int main() {
	int fd1, fd2;
	char buf[1000];
	int i;
	struct pollfd pfds[2];
	fd1 = open("file1.txt", O_RDONLY);
	fd2 = open("file2.txt", O_RDONLY);

	while (true) {
		pfds[0].fd = fd1;
		pfds[0].events = POLLIN;

		pfds[1].fd = fd2;
		pfds[1].events = POLLIN;

		poll(pfds, 2, 1);

		if (pfds[0].revents & POLLIN) {
			printf("Polling 1\n");
			i = read(fd1, buf, 1000);
			if (!i) {
				printf("stdin closed\n");
				return 0;
			}
			write(1, buf, i);
		}

		if (pfds[1].revents & POLLIN) {
			printf("Polling 2\n");
			i = read(fd2, buf, 1000);
			if (!i) {
				printf("stdin closed\n");
				return 0;
			}
			write(1, buf, i);
		}
	}
}