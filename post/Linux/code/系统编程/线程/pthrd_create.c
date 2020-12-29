#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    char ch;
    int var;
    char str[64];
} exit_t;

void *thrd_func(void *arg)
{
    exit_t *retvar = (exit_t *)arg;

    retvar->ch = 'm';
    retvar->var = 200;
    strcpy(retvar->str, "my thread");

    pthread_exit((void *)retvar);
}

int main(void)
{
    pthread_t tid;
    int ret;
    exit_t *retval = malloc(sizeof(exit_t));

    ret = pthread_create(&tid, NULL, thrd_func, (void *)retval);
    if (ret != 0) {
		// 将错误号转化为字符串
        fprintf(stderr, "pthread_create error:%s\n", strerror(ret));
        exit(1);
    }
    pthread_join(tid, (void **)&retval);
    printf("ch = %c, var = %d, str = %s\n", retval->ch, retval->var, retval->str);

    free(retval);
    pthread_exit((void *)1);
}

