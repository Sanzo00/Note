#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *thrd_func() {
	printf("In thread: pthread id = %lu, pid = %d\n", pthread_self(), getpid());
	return NULL;
}

int main() {

	pthread_t tid;
	int ret;

	printf("In main1: pthread id = %lu, pid = %d\n", pthread_self(), getpid());

	ret = pthread_create(&tid, NULL, thrd_func, NULL);
	if (ret != 0) {
		fprintf(stderr, "pthread_create error: %s\n", strerror(ret));
		printf("pthread_create error\n");
		exit(1);
	}
	// sleep(1);
	printf("In main2: pthread id = %lu, pid = %d\n", pthread_self(), getpid());
	// return 0;
	pthread_exit(NULL);
}
