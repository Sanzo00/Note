#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

void sys_err(char *s, int err) {
	fprintf(stderr, "%s error: %s\n", s, strerror(err));
	exit(1);
}

void *tfn1(void *arg) {
	printf("thread1 is running!\n");
	pthread_exit((void*)111);
}


void *tfn2(void *arg) {
	while (1) {
//		printf("thread2 is running!\n");
//		sleep(1);
		pthread_testcancel();
	}
	pthread_exit((void*)222);
}

int main() {
	pthread_t tid;
	int ret;
	void *retval;

	ret = pthread_create(&tid, NULL, tfn1, NULL);
	if (ret != 0) sys_err("pthread_create", ret);
	// pthread_detach(tid);
	ret = pthread_join(tid, (void**)&retval);
	if (ret != 0) sys_err("pthread_jon", ret);
	printf("thread1 retval: %d\n", (int)retval);

	ret = pthread_create(&tid, NULL, tfn2, NULL);
	if (ret != 0) sys_err("pthread_create", ret);
	
	sleep(3);

	ret = pthread_cancel(tid);
	if (ret != 0) sys_err("pthread_cancel", ret);
	ret = pthread_join(tid, (void**)&retval);
	if (ret != 0) sys_err("pthread_jon", ret);
	printf("thread2 retval: %d\n", (int)retval);

	return 0;
}
