#include <bits/stdc++.h>
#include <sys/select.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
using namespace std;


char buf[100];
string mainfifo = "/tmp/mainfifo",
		t1fifo = "/tmp/t1fifo",
		t2fifo = "/tmp/t2fifo",
		tmpfifo = "/tmp/tmpfifo";

int main() {

	mkfifo(mainfifo.c_str(), 0666);
	mkfifo(t1fifo.c_str(), 0666);
	mkfifo(t2fifo.c_str(), 0666);

	string myname;
	cout<<"Enter client Name: "; cin>>myname;
	int pid = getpid();

	stringstream ss;
	ss<<pid;
	string id;
	ss>>id;

	
	string msg = id;
	msg += " ";
	msg += myname;
	
	int fd = open(mainfifo.c_str(), O_WRONLY);
	write(fd, msg.c_str(), 100);
	
	while (true) {
		string service, tmsg = msg;
		cout<<"Enter the service required: "; cin>>service;
		tmsg += " ";
		tmsg += service;
		
		if (service == "service1" || service == "service2" || service == "service3") {
			int t1fd = open(t1fifo.c_str(), O_WRONLY);
			write(t1fd, tmsg.c_str(), 100);
		} else if (service == "service4" || service == "service5") {
			int t2fd = open(t2fifo.c_str(), O_WRONLY);
			write(t2fd, tmsg.c_str(), 100);
		} else {
			printf("Invalid request\n");
		}
	}
	
}