#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>


void *tfn1(void *arg)
{
	printf("thread 1 created\n");

	return (void *)111; 
}

void *tfn2(void *arg)
{
	printf("thread 2 created\n");
	pthread_exit((void *)222);
}

void *tfn3(void *arg)
{
	while (1) {
		// printf("thread 3: I'm going to die in 3 seconds ...\n");
		// sleep(1);

		pthread_testcancel();	//自己添加取消点
	}

    return (void *)666;
}

int main(void)
{
	pthread_t tid;
	void *tret = NULL;

	pthread_create(&tid, NULL, tfn1, NULL);
	pthread_join(tid, &tret);
	printf("thread 1 exit code = %d\n\n", (int)tret);

	pthread_create(&tid, NULL, tfn2, NULL);
	pthread_join(tid, &tret);
	printf("thread 2 exit code = %d\n\n", (int)tret);

	pthread_create(&tid, NULL, tfn3, NULL);
	sleep(3);
    pthread_cancel(tid);
	int ret = pthread_join(tid, &tret);
	printf("thread 3 exit code = %d\n", (int)tret);
	fprintf(stderr, "pthread_create error:%s\n", strerror(ret));
	return 0;
}

