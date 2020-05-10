#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

typedef struct {
	int a;
	int b;
}exit_t;

void *tfn(void *arg) {
	exit_t *ret = (exit_t *) arg;
	ret->a = 100;
	ret->b = 200;
	printf("thread: %p\n", ret);
	pthread_exit((void*) ret);
}

int main() {
  	// int pthread_join(pthread_t thread, void **retval);
	pthread_t tid;
	exit_t *retval = malloc(sizeof(exit_t));
	int ret;

	ret = pthread_create(&tid, NULL, tfn, (void *)retval);
	if (ret != 0) {
		fprintf(stderr, "pthread_create error: %s\n", strerror(ret));
		exit(1);
	}
	pthread_join(tid, (void **)&retval);
	printf("main: %p\n", retval);
	printf("a = %d, b = %d\n", retval->a, retval->b);
	free(retval);

	return 0;
}
