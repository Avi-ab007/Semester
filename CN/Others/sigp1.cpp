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

bool flag = false;

void receiveSignal(int sig) {
	if (sig == SIGUSR1)
		flag = false;
}

int main() {

	signal(SIGUSR1, receiveSignal);
	FILE* fp;
	int thisPid = getpid();
	int ret = mkfifo(pipeName.c_str(), 0666);
	if (ret < 0)
		cout<<"error in opening pipe\n";
	else
		cout<<"Pipe made\n";

	int fd = open(pipeName.c_str(), O_WRONLY);
	cout<<"fofo openmode()\n";
	stringstream ss;
	ss<<thisPid;
	string p1id;
	ss>>p1id;
	cout<<"Read from pipe\n";
	write(fd, p1id.c_str(), 100);
	close(fd);
	fp = fopen("text.txt", "r");
	int fn = fileno(fp);
	dup2(fn, 0);
	

	int p2pid;
	int c = fork();

	if (c > 0) {
		sleep(3);cout<<"Read from pipe\n";
		fd = open(pipeName.c_str(), O_RDONLY);
		char tmp[100];
		read(fd, tmp, 100);
		int p2pid = atoi(tmp);
		while (true) {
			while (!flag);
			printf("Program 1 reading file.\n");
			for (int i = 0; i < 5; i++) {
				cout<<i<<endl;
				if (!cin)
					return 0;
				string buf;
				getline(cin, buf);
				printf("%s\n", buf.c_str());
			}
			flag = true;
			kill(p2pid, SIGUSR1);
		}
	} else {
		char* proc[] = {"./sigp2", NULL};
		execvp(proc[0], proc);
	}
	
}