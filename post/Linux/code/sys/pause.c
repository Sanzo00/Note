#include <stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

void docatch(int signo) {
    return;
}

unsigned int mysleep(unsigned int seconds) {
    struct sigaction act, oldact;
    act.sa_handler = docatch;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    sigaction(SIGALRM, &act, &oldact);
    alarm(seconds);
    int ret = pause(); // 主动挂起 等待信号
    if (ret == -1 && errno == EINTR) {
        printf("pause sucess\n");
    }
    
    ret = alarm(0);
    sigaction(SIGALRM, &oldact, NULL); // 恢复SIGALRM的默认处理方式

    return ret;
}
int main() {
    while (1) {
        mysleep(2);
        printf("----------------\n");
    }
    return 0;
}
