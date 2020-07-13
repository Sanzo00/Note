#include <stdio.h>
#include <sys/time.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void myfunc(int signo) {
    printf("hello sanzo!\n");
}

int main() {
    struct itimerval it, oldit;
    signal(SIGALRM, myfunc); // 注册SIGALRM信号的捕捉处理函数
    it.it_value.tv_sec = 5;
    it.it_value.tv_usec = 0;

    it.it_interval.tv_sec = 3;
    it.it_interval.tv_usec = 0;

    int ret = setitimer(ITIMER_REAL, &it, &oldit);
    if (ret == -1) {
        perror("setitimer error");
        exit(1);
    }

    while (1);
    return 0;
}
