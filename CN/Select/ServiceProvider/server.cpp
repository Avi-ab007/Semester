#include <bits/stdc++.h>
#include <sys/select.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
using namespace std;

map<string, int> clientSet;

char mainbuf[100], t1buf[100], t2buf[100];
string mainfifo = "/tmp/mainfifo",
		t1fifo = "/tmp/t1fifo",
		t2fifo = "/tmp/t2fifo",
		tmpfifo = "/tmp/tmpfifo";

void service1(string clientName, string pid) {
	printf("Service 1 alloted to %s: %s\n", clientName.c_str(), pid.c_str());
	string msg = pid + " ";
	msg += clientName;
	msg += " granted service 1";
	return;
}

void service2(string clientName, string pid) {
	printf("Service 2 alloted to %s: %s\n", clientName.c_str(), pid.c_str());
	string msg = pid + " ";
	msg += clientName;
	msg += " granted service 2";
	return;
}

void service3(string clientName, string pid) {
	printf("Service 3 alloted to %s: %s\n", clientName.c_str(), pid.c_str());
	string msg = pid + " ";
	msg += clientName;
	msg += " granted service 3";
	return;
}

void outerService(string clientName, string pid, string service) {
	printf("Performing outer service\n");
	string msg = pid + " ";
	msg += clientName + " ";
	msg += service;
	int fd = open(tmpfifo.c_str(), O_WRONLY);
	write(fd, msg.c_str(), 100);
}


int main() {
	mkfifo(mainfifo.c_str(), 0666);
	mkfifo(t1fifo.c_str(), 0666);
	mkfifo(t2fifo.c_str(), 0666);
	mkfifo(tmpfifo.c_str(), 0666);

	fd_set readfds;


	int mainfd = open(mainfifo.c_str(), O_RDONLY|O_NONBLOCK);
	int t1fd = open(t1fifo.c_str(), O_RDONLY|O_NONBLOCK);
	int t2fd = open(t2fifo.c_str(), O_RDONLY|O_NONBLOCK);

	int MAX_FD = max(mainfd,max(t1fd,t2fd))+1;
	struct timeval timeout;
	int sret;

	while (true) {
		memset((void *)mainbuf, 0, 100);
		memset((void *)t1buf, 0, 100);
		memset((void *)t2buf, 0, 100);

		FD_ZERO(&readfds);
		
		timeout.tv_sec = 5;
		timeout.tv_usec = 0;

		FD_SET(t1fd, &readfds);
		FD_SET(t2fd, &readfds);
		FD_SET(mainfd, &readfds);

		sret = select(MAX_FD, &readfds, NULL, NULL, &timeout);
		if (sret == 0) {
			printf("Timeout\n");
		} else {
			if (FD_ISSET(mainfd, &readfds)) {
				printf("Client request received\n");
				int ret = read(mainfd, mainbuf, 100);
				if(ret<0) {
					printf("Error in reading \n"); 
					exit(0);
				}
				string req(mainbuf);
				stringstream ss;
				ss<<req;
				string pid, clientName;
				ss>>pid; ss>>clientName;
				printf("%s: %s sent join request\n", pid.c_str(), clientName.c_str());
			} 
			if (FD_ISSET(t1fd, &readfds)) {
				read(t1fd, t1buf, 100);
				string req(t1buf);
				stringstream ss;
				ss<<req;
				string pid, clientName, service;
				ss>>pid; ss>>clientName; ss>>service;
				int id = atoi(pid.c_str());
				if (service == "service1")
					service1(clientName, pid);
				else if (service == "service2")
					service2(clientName, pid);
				else if (service == "service3")
					service3(clientName, pid);
			}
			if (FD_ISSET(t2fd, &readfds)) {
				read(t2fd, t2buf, 100);
				string req(t2buf);
				stringstream ss;
				ss<<req;
				string pid, clientName, service;
				ss>>pid; ss>>clientName; ss>>service;
				outerService(clientName, pid, service);
			}
		}
	}
}