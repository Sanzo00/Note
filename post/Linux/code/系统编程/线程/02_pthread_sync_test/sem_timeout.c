#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define N 1024

sem_t s;

void *tfn(void *arg)
{
	char buf[N];

	while (1) {
		read(STDIN_FILENO, buf, N);
		sem_post(&s);
	}

	return NULL;
}

int main(void)
{
	pthread_t tid;
	struct timespec t = {0, 0};

	sem_init(&s, 0, 0);
	pthread_create(&tid, NULL, tfn, NULL);
	t.tv_sec = time(NULL) + 1;
	t.tv_nsec = 0;

	while (1) {
		sem_timedwait(&s, &t);
		printf(" hello world\n");
		t.tv_sec = time(NULL) + 5;
		t.tv_nsec = 0;
	}

	pthread_join(tid, NULL);
	sem_destroy(&s);

	return 0;
}
