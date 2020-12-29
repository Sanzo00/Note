#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct {
	int a;
	int b;
} exit_t;

void *tfn(void *arg)
{
	exit_t *ret;
	ret = malloc(sizeof(exit_t)); 

	ret->a = 100;
	ret->b = 300;

	pthread_exit((void *)ret);
}

int main(void)
{
	pthread_t tid;
	exit_t *retval;

	pthread_create(&tid, NULL, tfn, NULL);

	/*调用pthread_join可以获取线程的退出状态*/
	pthread_join(tid, (void **)&retval);      //wait(&status);
	printf("a = %d, b = %d \n", retval->a, retval->b);

	return 0;
}

