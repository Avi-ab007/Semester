#include <bits/stdc++.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <poll.h>
#include <sys/time.h>
#include <sys/shm.h>
#include <stdlib.h>
using namespace std;

#define SH_SIZE 100

int main() {
	int shmid;
	key_t key;
	char* shm, s;

	key = 875;
	shmid = shmget(key, SH_SIZE, IPC_CREAT | 0666);
	if (shmid < 0){
		perror("shmget");
		exit(0);
	}

	shm = (char*) shmat(shmid, NULL, 0);
	if (shm == (char*)-1){
		perror("shmat");
		exit(0);
	}

	memcpy(shm, "Hello World*", 100);

	while (*shm != '*')
		sleep(1);

	shmdt(shm);
	shmctl(shmid, IPC_RMID, 0);
	return 0;

}