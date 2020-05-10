#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void *tfn(void *arg) {
	printf("pthread id : %lu\n", pthread_self());
	pthread_exit(NULL);
}

int main() {

	// int pthread_detach(pthread_t thread);
	// 线程主动和主控线程断开关系，线程结束后退出状态不由其他线程获取，直接释放，无系统残留资源
	pthread_t tid;
	int ret, err;
	void *tret;
	
	ret = pthread_create(&tid, NULL, tfn, NULL);
	if (ret != 0) {
		fprintf(stderr, "pthread_create error: %s\n", strerror(ret));
		exit(1);
	}
	pthread_detach(tid);
	while(1) {
		err = pthread_join(tid, (void **)&tret);
		printf("pthread err: %d\n", err);
		if (err != 0) {
			fprintf(stderr, "pthread_join error: %s\n", strerror(err));
		}else {
			fprintf(stderr, "thread exit code: %d\n", (int)tret);
		}
		sleep(1);
	}

	return 0;
}
