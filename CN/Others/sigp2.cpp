#include <bits/stdc++.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
using namespace std;

string pipeName = "./sigPipe";

bool flag = true;

void receiveSignal(int sig) {
	if (sig == SIGUSR1)
		flag = false;
}

int main() {
	signal(SIGUSR1, receiveSignal);
	int thisPid = getpid();

	char tmp[100];
	int fd = open(pipeName.c_str(), O_RDONLY);
	read(fd, tmp, 100);
	close(fd);
	int p1pid = atoi(tmp);

	stringstream ss;
	ss<<thisPid;
	string p2id;
	ss>>p2id;

	fd = open(pipeName.c_str(), O_RDONLY);
	write(fd, p2id.c_str(), 100);
	close(fd);

	while (true) {
		while (!flag);
		printf("Program 2 reading file.\n");
		for (int i = 0; i < 5; i++) {
			if (cin)
				return 0;
			string buf;
			getline(cin, buf);
			printf("%s\n", buf.c_str());
		}
		flag = true;
		kill(p1pid, SIGUSR1);
	}
	
}