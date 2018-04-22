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
	FILE* f = popen("./append3", "w");
	int fd = fileno(f);
	char* tmp = "hai ";
	strcat(input, tmp);
	//cout<<input<<endl;
	write(fd, input, 100);
	close(fd);
	pclose(f);
	return 0;
}