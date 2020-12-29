#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

void *tfn(void *arg)
{
	int n = 3;

	while (n--) {
		printf("thread count %d\n", n);
		sleep(1);
	}

	//return (void *)1;
    pthread_exit((void *)1);
}

int main(void)
{
	pthread_t tid;
	void *tret;
	int err;

#if 0

	pthread_attr_t attr;			/*通过线程属性来设置游离态*/
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,	PTHREAD_CREATE_DETACHED);
	pthread_create(&tid, &attr, tfn, NULL);

#else

	pthread_create(&tid, NULL, tfn, NULL);
	pthread_detach(tid);         //让线程分离  ----自动退出,无系统残留资源

#endif

	while (1) {
		err = pthread_join(tid, &tret);
        printf("-------------err= %d\n", err);
		if (err != 0)
			fprintf(stderr, "thread_join error: %s\n", strerror(err));
		else
			fprintf(stderr, "thread exit code %d\n", (int)tret);

		sleep(1);
	}

	return 0;
}


