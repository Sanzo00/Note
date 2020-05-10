#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
int counter;
pthread_rwlock_t rwlock;

void *th_write(void *arg) {
	int t;
	int i = (int) arg;
	printf("i = %d\n", i);
	while (1) {
		t = counter;
		usleep(1000);
		pthread_rwlock_wrlock(&rwlock);
		printf("write %d: %lu: counter = %d ++counter = %d\n", i, pthread_self(), t, ++counter);
		pthread_rwlock_unlock(&rwlock);
		usleep(1000);
	}
	return NULL;
}

void *th_read(void *arg) {
	int i;
	i = (int) arg;
	while (1) {
		pthread_rwlock_rdlock(&rwlock);
		printf("read %d: %lu: counter = %d\n", i, pthread_self(), counter);
		pthread_rwlock_unlock(&rwlock);
		usleep(900);
	}
	return NULL;
}

void sys_err(char *s, int err) {
	fprintf(stderr, "%s error: %s\n", s, strerror(err));
	exit(1);
}
int main() {

	int i, ret;
	pthread_t tid[8];
	pthread_rwlock_init(&rwlock, NULL);
	
	// 创建3个写线程
	for (i = 0; i < 3; ++i) {
		ret = pthread_create(&tid[i], NULL, th_write, (void*)i);
		if (ret != 0) sys_err("pthread_create", ret);
	}
	// 创建5个读线程
	for (int i = 0; i < 5; ++i) {
		ret = pthread_create(&tid[i+3], NULL, th_read, (void*)i+1);
		if (ret != 0) sys_err("pthread_create", ret);
	}
	// 释放读写锁
	pthread_rwlock_destroy(&rwlock);
	pthread_exit(NULL);
	// return 0;
}
