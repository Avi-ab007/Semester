#include <bits/stdc++.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
using namespace std;

char buf[10];
string buffer = "";
string 	pipe_header = "/tmp/",
		c1_pipe, writeTo_pipe;
int MAX_FDS ;

static void performService(int sig) {
	int fd = open(writeTo_pipe.c_str(), O_WRONLY);
	write(fd, buffer.c_str(), buffer.size());
	buffer = "";
	close(fd);
	return;
}

int main() {
	signal(SIGUSR1, performService);
	c1_pipe = pipe_header;
	c1_pipe += "c1";
	mkfifo(c1_pipe.c_str(), 0666);
	int sfd = open(c1_pipe.c_str(), O_WRONLY);
	int pid = getpid();
	string tmp;
	stringstream ss; ss<<pid;
	ss>>tmp;
	cout<<tmp<<endl;
	write(sfd, tmp.c_str(), 10);
	close(sfd);
	bool flag = true;
	writeTo_pipe = pipe_header;
	writeTo_pipe += "writeTo";
	mkfifo(writeTo_pipe.c_str(), 0666);

	fd_set readfds, writefds;
	

	int kbdfd = 0, filefd = open("text.txt", O_RDONLY);
	MAX_FDS = filefd + 1;
	while (true) {
		FD_ZERO(&readfds);
		FD_ZERO(&writefds);

		struct timeval timeout;
		timeout.tv_sec = 5;
		timeout.tv_usec = 0;

		FD_SET(kbdfd, &readfds);
		if (flag)
			FD_SET(filefd, &readfds);

		int sret = select(MAX_FDS, &readfds, NULL, NULL, &timeout);
		if (sret == 0) {
			printf("sret = %d\n", sret);
			printf("Timeout\n");
		} else {
			memset((void *)buf, 0, 10);
			if (FD_ISSET(kbdfd, &readfds)) {
				printf("Reading from keyboard\n");
				read(kbdfd, (void *)buf, 10);
				printf("\t%s\n", buf);
				buffer += string(buf);
			} 
			if (FD_ISSET(filefd, &readfds)) {
				printf("Reading from file\n");
				read(filefd, (void *)buf, 10);
				if (buf[0] == '$'){
					flag = false;
					FD_CLR(filefd, &readfds);
				}
				printf("\t%s\n", buf);
				sleep(1);
				buffer += string(buf);
			}
		}

	}
}