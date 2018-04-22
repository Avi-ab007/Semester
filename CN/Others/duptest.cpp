#include <bits/stdc++.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
using namespace std;

int main() {
	FILE* f = popen("./append", "w");
	int fd = fileno(f);
	char* msg = "avi";
	write(fd, msg, 100);
	close(fd);
	pclose(f);
	return 0;
}