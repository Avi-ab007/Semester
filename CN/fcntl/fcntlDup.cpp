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
	if (fd < 0)
		perror("opening file\n");
	int nfd = fcntl(fd, F_DUPFD, 0);
	//close(fd);
	//char* argv[] = {"./dup2p2", NULL, NULL};
	char ch;
	while (true) {
		if (read(nfd, &ch, 1) <= 0)
			break;
		printf("%c", ch);
	}

	return 0;
}