#include <stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

void docatch(int signo) {
    return;
}

unsigned int mysleep(unsigned int seconds) {
    sigset_t newmask, oldmask, suspmask;
    struct sigaction act, oldact;
    unsigned int unslept;

    // 为SIGALRM设置捕捉函数
    act.sa_handler = docatch;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGALRM, &act, &oldact);

    // 设置阻塞信号集, 阻塞SIGALRM
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGALRM);
    sigprocmask(SIG_BLOCK, &newmask, &oldmask);

    // 定时
    alarm(seconds);

    // 调用sigsuspend, 使用临时有效的阻塞信号集
    // 在临时阻塞集合中解除SIGALRM信号的阻塞
    // sigsuspend完成之后, 恢复之前的阻塞信号集
    suspmask = oldmask;
    sigdelset(&suspmask, SIGALRM);
    sigsuspend(&suspmask); // 原子操作

    unslept = alarm(0);
    // 恢复SIGALRM原有的处理动作
    sigaction(SIGALRM, &oldact, NULL);

    // 解除对SIGALRM的阻塞, 恢复之前的阻塞信号集
    sigprocmask(SIG_SETMASK, &oldmask, NULL);
    return unslept;
}
int main() {
    while (1) {
        mysleep(2);
        printf("----------------\n");
    }
    return 0;
}
