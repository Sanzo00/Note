#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_cond_t has_product = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

struct msg{
	struct msg *next;
	int num;
};
struct msg *head, *mp;

void *consumer(void *arg) {
	while (1) {
		pthread_mutex_lock(&lock);
		while (head == NULL) { // 多个消费者, 只有一个能抢到资源
			pthread_cond_wait(&has_product, &lock);
		}
		mp = head;
		head = mp->next;
		pthread_mutex_unlock(&lock);

		printf("Consumer -- %d\n", mp->num);
		free(mp);
		mp = NULL;
		sleep(rand() % 3);
	}
}

void *producer(void *p) {
	while (1) {
		mp = malloc(sizeof(struct msg));
		mp->num = rand() % 100 + 1;
		printf("Producer ++ %d\n", mp->num);
		
		pthread_mutex_lock(&lock);
		mp->next = head;
		head = mp;
		pthread_mutex_unlock(&lock);
		// 唤醒等待的线程
		pthread_cond_signal(&has_product); 
		sleep(rand() % 3);
	}
}

int main() {
	pthread_t pid, cid;
	srand(time(NULL));

	pthread_create(&pid, NULL, producer, NULL);
	pthread_create(&cid, NULL, consumer, NULL);

	pthread_join(pid, NULL);
	pthread_join(cid, NULL);

	return 0;
}
