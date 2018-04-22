#include <sys/ioctl.h>
#include <unistd.h>
#include <linux/kd.h>
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

#define ERROR -1
int fd;

void sighandler(int sig) {
	if ((ioctl(fd, KDSETLED, 0x0)) == ERROR) {
		perror("ioctl");
		close(fd);
		exit(ERROR);
	}

	printf("\nw00w00!\n");
	close(fd);
	exit(0);
}

int main() {
	int i;
	if ((fd = open("/dev/console", O_NOCTTY)) == ERROR) {
		perror("open");
		exit(ERROR);
	}

	signal(SIGINT, sighandler);
	signal(SIGTERM, sighandler);
	signal(SIGQUIT, sighandler);
	signal(SIGTSTP, sighandler);

	printf("w00w00!\n\n");
	printf("Hit exit Control-c\n");

	while (true) {
		for (i = 0x01; i <= 0x004; i++) {
			if (i == 0x03)
			continue;

			// usleep(500000);
			sleep(1);

			if ((ioctl(fd, KDSETLED, i)) == ERROR) {
				perror("ioctl");
				close(fd);
				exit(0);
			}			
		}
	}
	close(fd);
}