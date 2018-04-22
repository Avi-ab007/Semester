#include <bits/stdc++.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>
using namespace std;

sem_t sem_x, sem_y;

void* P1(void* data) {
	while(true) {
		sem_wait(&sem_x);
		
	}
}
int main() {
	pthread_t tp1, tp2;
	sem_init(&sem_x, 0, 1);
	sem_init(&sem_y, 1, 1);

	pthread_create(&tp1, NULL, P1, NULL);
	pthread_create(&tp2, NULL, P2, NULL);

	pthread_join(tp1, NULL);
	pthread_join(tp2, NULL);
}