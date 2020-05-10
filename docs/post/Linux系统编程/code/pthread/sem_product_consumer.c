#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#define NUM 5

int queue[NUM];
sem_t blank_number, product_number;

void *producer(void *arg) {
	int i = 0;
	while (1) {
		sem_wait(&blank_number);
		queue[i] = rand() % 100 + 1;
		printf("Produce ++ %d\n", queue[i]);
		sem_post(&product_number);

		i = (i + 1) % NUM;
		sleep(rand() % 1);
	}
}

void *consumer(void *arg) {
	int i = 0;
	while (1) {
		sem_wait(&product_number);
		printf("Consume -- %d\n", queue[i]);
		queue[i] = 0;
		i = (i + 1) % NUM;
		sleep(rand() % 3);
	}
}

int main() {
	pthread_t pid, cid;

	sem_init(&blank_number, 0, NUM);
	sem_init(&product_number, 0, 0);

	pthread_create(&pid, NULL, producer, NULL);
	pthread_create(&cid, NULL, consumer, NULL);

	pthread_join(pid, NULL);
	pthread_join(cid, NULL);

	sem_destroy(&blank_number);
	sem_destroy(&product_number);

	return 0;
}
