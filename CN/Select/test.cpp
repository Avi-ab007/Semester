#include <bits/stdc++.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
using namespace std;

int main() {
	int sret, fd = 0;
	char buf[11];
	
	fd_set readfds;
	struct timeval timeout;

	while (true) {
		FD_ZERO(&readfds);
		FD_SET(fd, &readfds);

		timeout.tv_sec = 3;
		timeout.tv_usec = 0;

		sret = select(1, &readfds, NULL, NULL, &timeout);

		if (sret == 0) {
			printf("sret = %d\n", sret);
			printf("\ttimeout\n");
		} else {
			printf("sret = %d\n", sret);
			memset((void *)buf, 0, 11);

			if (read(fd, (void *)buf, 10)) {
				buf[10] = '\0';
				printf("\tbuf = %s\n", buf);
			}
		}
	}
}
