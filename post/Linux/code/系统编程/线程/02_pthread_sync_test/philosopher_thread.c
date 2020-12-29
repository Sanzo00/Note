#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

pthread_mutex_t m[5];

void *tfn(void *arg)
{
	int i, l, r;

	srand(time(NULL));
	i = (int)arg;

	if (i == 4)
		l = 0, r = i;
	else
		l = i; r = i+1;

	while (1) {
		pthread_mutex_lock(&m[l]);
		if (pthread_mutex_trylock(&m[r]) == 0) {
			printf("\t%c is eating \n", 'A'+i);
			pthread_mutex_unlock(&m[r]);
		}
		pthread_mutex_unlock(&m[l]);
		sleep(rand() % 5);
	}

	return NULL;
}

int main(void)
{
	int i;
	pthread_t tid[5];
	
	for (i = 0; i < 5; i++)
		pthread_mutex_init(&m[i], NULL);

	for (i = 0; i < 5; i++)
		pthread_create(&tid[i], NULL, tfn, (void *)i);

	for (i = 0; i < 5; i++)
		pthread_join(tid[i], NULL);

	for (i = 0; i < 5; i++)
		pthread_mutex_destroy(&m[i]);

	return 0;
}

