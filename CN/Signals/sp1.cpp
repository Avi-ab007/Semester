#include <bits/stdc++.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
using namespace std;

bool flag;
int p2pid, fd;
void ReadHandler(int sig) {
	cout<<"Program 1 is reading.\n";
	char ch;
	int cnt = 0;
	while (cnt < 5) {
		if (read(fd, &ch, 1) == 0) {
			//fclose(scanf);
			flag = true;
		}
		printf("%c", ch);
		if (ch == '\n')
			cnt++;
	}
	kill(p2pid, SIGUSR2);
}

int main() {
	signal(SIGUSR1, ReadHandler);
	flag = false;
	fd = open("text.txt", O_RDONLY);
	dup2(fd, 0);
	int c = fork();
	p2pid = c;
	if (c > 0) {
		while (!flag);
	} else {
		execvp("./sp2", NULL);
	}
}