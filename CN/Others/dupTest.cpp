#include <bits/stdc++.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h> 
#include <unistd.h>
using namespace std;

int main() {
	int fd = open("text.txt", O_RDONLY);
	dup2(fd, 0);
	char str[100];
	fgets(str, 100, stdin);
	printf("%s\n", str);
	return
}