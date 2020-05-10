#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

struct mt{
	int num;
	pthread_mutex_t mutex;
	pthread_mutexattr_t mutexattr;
};

int main() {
	int i;
	struct mt *mm;
	pid_t pid;

	mm = mmap(NULL, sizeof(*mm), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANON, -1, 0);
	memset(mm, 0, sizeof(*mm));
	// 初始化mutex属性对象
	pthread_mutexattr_init(&mm->mutexattr);
	// 设置进程共享
	pthread_mutexattr_setpshared(&mm->mutexattr, PTHREAD_PROCESS_SHARED);
	// 初始化mutex锁
	pthread_mutex_init(&mm->mutex, &mm->mutexattr);

	pid = fork();
	if (pid == 0) {
		for (i = 0; i < 10; ++i) {
			pthread_mutex_lock(&mm->mutex);
			(mm->num)++;
			pthread_mutex_unlock(&mm->mutex);
			printf("child num++ %d\n", mm->num);

			sleep(1);
		}
	}else if(pid > 0) {
		for (i = 0; i < 10; ++i) {
			sleep(1);
			pthread_mutex_lock(&mm->mutex);
			mm->num += 2;
			printf("parent num +=2 %d\n", mm->num);
			pthread_mutex_unlock(&mm->mutex);
		}
		wait(NULL);
	}
	pthread_mutexattr_destroy(&mm->mutexattr);
	pthread_mutex_destroy(&mm->mutex);
	return 0;
}
