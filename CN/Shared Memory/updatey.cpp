#include <bits/stdc++.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <poll.h>
#include <sys/time.h>
#include <sys/shm.h>
#include <stdlib.h>
using namespace std;

string sharePipe = "/tmp/sharePipe";
int ppid;
bool flag = true;

void static updateY(int sig) {
	sleep(1);
	int fd = open(sharePipe.c_str(), O_RDONLY);
	char input[100];
	read(fd, input, 100);
	close(fd);

	printf("In program 2\n");
	string read(input);
	stringstream ss;
	ss<<read;
	int x, y;
	ss>>x;
	ss>>y;
	printf("X : %d, Y : %d\n", x, y);
	y = x + 1;
	
	kill(ppid, SIGUSR1);
	
	string sx = to_string(x);
	string sy = to_string(y);
	sx += " ";
	sx += sy;

	fd = open(sharePipe.c_str(), O_WRONLY);
	write(fd, sx.c_str(), 100);
	close(fd);

}

int main() {
	printf("PRogram 2 started.\n");
	ppid = getppid();
	signal(SIGUSR2, updateY);

	string tmp = "1 1";
	kill(ppid, SIGUSR1);
	int ds = open(sharePipe.c_str(), O_WRONLY);
	write(ds, tmp.c_str(), 100);
	close(ds);
	while(flag);
}