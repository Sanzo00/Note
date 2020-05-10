#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

void *tfn(void *arg){
	pthread_exit(NULL);
}

int main() {
	pthread_t tid;
	int ret;
	pthread_attr_t attr;
	void* retval;

	ret = pthread_attr_init(&attr);
	if (ret != 0) {
		if (ret != 0) {
			fprintf(stderr, "pthread_attr_init error: %s\n", strerror(ret));
			exit(1);
		}
	}

	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	ret = pthread_create(&tid, &attr, tfn, NULL);

	if (ret != 0) {
		fprintf(stderr, "pthread_create error: %s\n", strerror(ret));
		exit(1);
	}
	
	ret = pthread_join(tid, (void**)&retval);
	printf("pthread_join ret: %d\n", ret);
	
	pthread_attr_destroy(&attr);
	return 0;
}
