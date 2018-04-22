#include <bits/stdc++.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
using namespace std;
int fd;
string pipe_name = "/tmp/";
std::vector<string> client_pipes;


int main(){
	string fifo_name = pipe_name + "server";
	mkfifo(fifo_name.c_str(), 0666);

	while (true) {
		fd = open(fifo_name.c_str(), O_RDONLY);
		char tmp[100];
		read(fd, tmp, 100);
		string input(tmp);
		int pos = input.find(" ");
		string inst = input.substr(0, pos);
		if (inst == "join") {
			string clientName = input.substr(pos+1, input.length());
			string temp = pipe_name + clientName;
			mkfifo(temp.c_str(), 0666);
			client_pipes.push_back(clientName);
			close(fd);
		}
		////////////////////////////////////////////////////////
		else {
			for (int i = 0; i < client_pipes.size(); i++) {
				if (inst != client_pipes[i]) {
					string clientPipe = pipe_name + client_pipes[i];
					int tfd = open(clientPipe.c_str(), O_WRONLY);
					//string msg = s.substr(pos+1, s.length());
					write(tfd, input.c_str(), 100);
					close(tfd);
				}
			}
		}
	}

	return 0;

}