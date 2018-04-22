#include <bits/stdc++.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h> 
#include <unistd.h>
using namespace std;

int main() {
	pid_t pid;
	int fd = open("text.txt", O_RDONLY);
	dup2(fd, 0);
	//char* argv[] = {"./dup2p2", NULL, NULL};
	pid = fork();
	if (pid > 0)
		wait(NULL);
	if (pid == 0)
		execvp("./p1", NULL);

	return 0;
}