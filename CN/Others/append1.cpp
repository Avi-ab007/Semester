#include <bits/stdc++.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h> 
#include <unistd.h>
using namespace std;

int main() {
	char input[100];
	cin>>input;
	char* tmp = " vidhayak ";
	FILE* f = popen("./append2", "w");
	int fd = fileno(f);
	strcat(input, tmp);
	//cout<<input<<endl;
	write(fd, tmp, 100);
	close(fd);
	pclose(f);
	return 0;
}