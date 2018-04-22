#include <bits/stdc++.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <poll.h>
#include <sys/time.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <stdlib.h>
using namespace std;

string sharePipe = "/tmp/sharePipe";
int cpid;

void static updateX(int sig) {
	sleep(1);
	int fd = open(sharePipe.c_str(), O_RDONLY);
	char input[100];
	read(fd, input, 100);
	close(fd);

	printf("In program 1\n");
	string read(input);
	stringstream ss;
	ss<<read;
	int x, y;
	ss>>x;
	ss>>y;
	printf("X : %d, Y : %d\n", x, y);
	x = y + 1;
	
	kill(cpid, SIGUSR2);
	string sx = to_string(x);
	string sy = to_string(y);
	sx += " ";
	sx += sy;

	fd = open(sharePipe.c_str(), O_WRONLY);
	write(fd, sx.c_str(), 100);
	close(fd);

}

int main() {
	mkfifo(sharePipe.c_str(), 0666);
	printf("Program 1 started.\n");

	signal(SIGUSR1, updateX);
	cpid = fork();

	if (cpid > 0) {
		while(true);
	} else {
		execvp("./p2", NULL);
	}
}