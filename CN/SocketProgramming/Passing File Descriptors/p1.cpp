#include <bits/stdc++.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <pthread.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
using namespace std;

int main() {
	int fd, usfd[2], status;
	pid_t cpid;

	fd = open("./text.txt", O_RDONLY);
	socketpair(AF_LOCAL, SOCK_STREAM, 0, usfd);

	int c = fork();
	if (c == 0) {
		close(usfd[1]);
		execvp("./p2", NULL);
	} else {
		close(usfd[0]);
	}
}