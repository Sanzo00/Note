#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>


void *tfn(void *arg)
{
    while (1)
        sleep(1);
}

int main(void)
{
	pthread_t tid;
	int ret, count = 1;

	for (;;) {
		ret = pthread_create(&tid, NULL, tfn, NULL);
		if (ret != 0) {
			printf("%s\n", strerror(ret));
			break;
		}
		printf("---------%d\n", ++count);
	}

	return 0;
}

