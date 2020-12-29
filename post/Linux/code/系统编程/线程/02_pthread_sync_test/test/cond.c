#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

struct msg {
    int num;
    struct msg *next;
};

struct msg *head = NULL;
struct msg *mp = NULL;

pthread_cond_t has_product = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *producter(void *p)
{
    while (1) {
        mp = malloc(sizeof(struct msg));
        mp->num = rand() % 1000 + 1;
        printf("---product----%d\n", mp->num);

        pthread_mutex_lock(&mutex);
        mp->next = head;
        head = mp;
        pthread_mutex_unlock(&mutex);

        pthread_cond_signal(&has_product);
        sleep(rand() % 2);
    }

    return NULL;
}

void *consumer(void *p)
{
    while (1) {
        pthread_mutex_lock(&mutex);
        while (head == NULL)
            pthread_cond_wait(&has_product, &mutex);
        mp = head;
        head = mp->next;
        pthread_mutex_unlock(&mutex);

        printf("-----------------consumer---%d\n", mp->num);
        free(mp);
        mp = NULL;
        sleep(rand() % 3);
    }

    return NULL;
}

int main(void)
{
    pthread_t pid, cid;
    srand(time(NULL));

    pthread_create(&pid, NULL, producter, NULL);
    pthread_create(&cid, NULL, consumer, NULL);

    pthread_join(pid, NULL);
    pthread_join(cid, NULL);

    return 0;
}
