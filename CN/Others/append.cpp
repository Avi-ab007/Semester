#include <bits/stdc++.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
using namespace std;

int main() {
	string temp;
	cin>>temp;
	FILE* fp = popen("./append1", "w");
	int fd = fileno(fp);
	write(fd, temp.c_str(), 100);
	close(fd);
	pclose(fp);
}