#include <unistd.h>
#include <signal.h>
#include <stdio.h>

void sig_alrm(int signo)
{
    /* nothing to do */
}

unsigned int mysleep(unsigned int nsecs)
{
    struct sigaction newact, oldact;
    sigset_t newmask, oldmask, suspmask;
    unsigned int unslept;

    //1.为SIGALRM设置捕捉函数，一个空函数
    newact.sa_handler = sig_alrm;
    sigemptyset(&newact.sa_mask);
    newact.sa_flags = 0;
    sigaction(SIGALRM, &newact, &oldact);

    //2.设置阻塞信号集，阻塞SIGALRM信号
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGALRM);
   sigprocmask(SIG_BLOCK, &newmask, &oldmask);   //信号屏蔽字 mask

    //3.定时n秒，到时后可以产生SIGALRM信号
    alarm(nsecs);

    /*4.构造一个调用sigsuspend临时有效的阻塞信号集，
     *  在临时阻塞信号集里解除SIGALRM的阻塞*/
    suspmask = oldmask;
    sigdelset(&suspmask, SIGALRM);

    /*5.sigsuspend调用期间，采用临时阻塞信号集suspmask替换原有阻塞信号集
     *  这个信号集中不包含SIGALRM信号,同时挂起等待，
     *  当sigsuspend被信号唤醒返回时，恢复原有的阻塞信号集*/
    sigsuspend(&suspmask); 

    unslept = alarm(0);
    //6.恢复SIGALRM原有的处理动作，呼应前面注释1
    sigaction(SIGALRM, &oldact, NULL);

    //7.解除对SIGALRM的阻塞，呼应前面注释2
    sigprocmask(SIG_SETMASK, &oldmask, NULL);

    return(unslept);
}

int main(void)
{
    while(1){
        mysleep(2);
        printf("Two seconds passed\n");
    }

    return 0;
}
