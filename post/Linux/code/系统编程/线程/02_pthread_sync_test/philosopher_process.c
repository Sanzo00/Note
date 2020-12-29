#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/wait.h>

int main(void)
{
	int i;
	pid_t pid;

	sem_t *s;
	s = mmap(NULL, sizeof(sem_t)*5, PROT_READ|PROT_WRITE, 
			MAP_SHARED|MAP_ANON, -1, 0);
	if (s == MAP_FAILED) {
		perror("fail to mmap");
		exit(1);
	}

	for (i = 0; i < 5; i++)
		sem_init(&s[i], 0, 1);  //信号量初值制定为1，信号量，变成了互斥锁

	for (i = 0; i < 5; i++)
		if ((pid = fork()) == 0)
			break;

	if (i < 5) {				//子进程
		int l, r;
		srand(time(NULL));

		if (i == 4) 
			l = 0, r = 4;
		else
			l = i, r = i+1;
		while (1) {
			sem_wait(&s[l]);
			if (sem_trywait(&s[r]) == 0) {
				printf(" %c is eating\n", 'A'+i);
				sem_post(&s[r]);
			}
			sem_post(&s[l]);
			sleep(rand() % 5);
		}
		exit(0);
	} 

	for (i = 0; i < 5; i++)
		wait(NULL);	

	for (i = 0; i < 5; i++)
		sem_destroy(&s[i]);

	munmap(s, sizeof(sem_t)*5);

	return 0;
}

