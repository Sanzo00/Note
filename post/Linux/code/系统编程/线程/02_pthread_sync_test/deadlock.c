#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#if 0

int var = 1, num = 5;
pthread_mutex_t m_var, m_num;

void *tfn(void *arg)
{
    int i = (int)arg;

    if (i == 1) {

        pthread_mutex_lock(&m_var);
        var = 22;
        sleep(1);       //给另外一个线程加锁,创造机会.

        pthread_mutex_lock(&m_num);
        num = 66; 

        pthread_mutex_unlock(&m_var);
        pthread_mutex_unlock(&m_num);

        printf("----thread %d finish\n", i);
        pthread_exit(NULL);

    } else if (i == 2) {

        pthread_mutex_lock(&m_num);
        var = 33;
        sleep(1);

        pthread_mutex_lock(&m_var);
        num = 99; 

        pthread_mutex_unlock(&m_var);
        pthread_mutex_unlock(&m_num);

        printf("----thread %d finish\n", i);
        pthread_exit(NULL);
    }

    return NULL;
}

int main(void)
{
    pthread_t tid1, tid2;
    int ret1, ret2;

    pthread_mutex_init(&m_var, NULL);
    pthread_mutex_init(&m_num, NULL);

    pthread_create(&tid1, NULL, tfn, (void *)1);
    pthread_create(&tid2, NULL, tfn, (void *)2);

    sleep(3);
    printf("var = %d, num = %d\n", var, num);

    ret1 = pthread_mutex_destroy(&m_var);      //释放琐
    ret2 = pthread_mutex_destroy(&m_num);
    if (ret1 == 0 && ret2 == 0) 
        printf("------------destroy mutex finish\n");

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    printf("------------join thread finish\n");

    return 0;
}
#else 

int a = 100;

int main(void)
{
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    pthread_mutex_lock(&mutex);
    a = 777;
    pthread_mutex_lock(&mutex);

    pthread_mutex_unlock(&mutex);

    printf("-----------a = %d\n", a);
    pthread_mutex_destroy(&mutex);

    return 0;
}

#endif
