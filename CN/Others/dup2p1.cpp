#include <bits/stdc++.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h> 
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

int main() {
	char input[100];
	bool flag = true;
	int cnt = 0;
	char ch;
	printf("Program 1 reading.\n");
	while (cnt < 5) {
		if (scanf("%c", &ch) < 0) {
			//fclose(scanf);
			return 0;
		}
		printf("%c", ch);
		if (ch == '\n')
			cnt++;
	}
	pid_t pid;
	//char* argv[] = {"./dup2p2", NULL, NULL};
	pid = fork();
	if (pid == 0)
		execvp("./p2", NULL);

	return 0;
}