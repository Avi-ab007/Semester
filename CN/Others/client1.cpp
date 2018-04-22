#include <bits/stdc++.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
using namespace std;
string pipe_name = "/tmp/";
string clientName;

void* READ(void* data) {
	while (true) {
		string pipeName = pipe_name + clientName;
		int fd = open(pipeName.c_str(), O_RDONLY);
		char tmp[100];
		read(fd, tmp, 100);
		string input(tmp);
		int pos = input.find(" ");
		string user = input.substr(0, pos);
		string msg = input.substr(pos+1, input.length());
		cout<<user<<" : "<<msg<<endl;
		//printf("%s: %s\n", user.c_str(), msg.c_str());
		close(fd);
	}
}

void* WRITE(void* data) {
	while (true) {
		string serverPipe = pipe_name + "server";
		int fd = open(serverPipe.c_str(), O_WRONLY);
		string ms;
		cin>>ms;
		string msg = clientName;
		msg += " ";
		msg += ms;
		write(fd, msg.c_str(), 100);
		close(fd);
	}
}
int main() {
	pthread_t rd, wr;
	printf("Enter client name: \n");
	cin>>clientName;

	string serverPipe = pipe_name;
	serverPipe += "server";
	int fd = open(serverPipe.c_str(), O_WRONLY);
	string join_server_message = "join ";
	join_server_message += clientName;
	write(fd, join_server_message.c_str(), 100);
	close(fd);

	pthread_create(&rd, NULL, READ, NULL);
	pthread_create(&wr, NULL, WRITE, NULL);

	pthread_join(rd, NULL);
	pthread_join(wr, NULL);
}