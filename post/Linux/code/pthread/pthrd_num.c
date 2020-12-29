#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
void *tfn(void *arg) {
	int i = (int) arg;
	printf("%dth pthread\n", i+1);
	while(1);
	pthread_exit(NULL);
}

int main() {

	pthread_t tid;
	int cnt = 0;
	while (1) {
		pthread_create(&tid, NULL, tfn, (void*)cnt++);
	}

	return 0;
}
