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

int main () {
	string pipe = "/tmp/pipe1";
	printf("Client 1 waiting for input\n");
	char buf[] = "Hello from client 1";
	int cnt = 3;
	int fd = open(pipe.c_str(), O_WRONLY);
	while (cnt--) {
		write(fd, buf, 100);
		sleep((rand()%100)/50.0);
	}
	close(fd);
	return 0;
}
