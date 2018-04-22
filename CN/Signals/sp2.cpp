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
int fd;
void ReadHandler(int sig) {
	cout<<"Program 2 is reading.\n";
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
	kill(getppid(), SIGUSR1);
}

int main() {
	signal(SIGUSR2, ReadHandler);
	flag = false;
	dup2(0, fd);
	kill(getppid(), SIGUSR1);
	while (!flag);
}