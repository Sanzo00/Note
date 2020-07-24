#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#if 0

siginfo_t {
    int      si_signo;    /* Signal number */
    int      si_errno;    /* An errno value */
    int      si_code;     /* Signal code */
    int      si_trapno;   /* Trap number that caused
                             hardware-generated signal
                             (unused on most architectures) */
    pid_t    si_pid;      /* Sending process ID */
    uid_t    si_uid;      /* Real user ID of sending process */
    int      si_status;   /* Exit value or signal */
    clock_t  si_utime;    /* User time consumed */
    clock_t  si_stime;    /* System time consumed */
    sigval_t si_value;    /* Signal value */
    int      si_int;      /* POSIX.1b signal */
    void    *si_ptr;      /* POSIX.1b signal */
    int      si_overrun;  /* Timer overrun count; POSIX.1b timers */
    int      si_timerid;  /* Timer ID; POSIX.1b timers */
    void    *si_addr;     /* Memory location which caused fault */
    long     si_band;     /* Band event (was int in
                             glibc 2.3.2 and earlier) */
    int      si_fd;       /* File descriptor */
    short    si_addr_lsb; /* Least significant bit of address
                             (since Linux 2.6.32) */
}

union sigval {
   int   sival_int;
   void *sival_ptr;
};
#endif

void func(int signo, siginfo_t *uinfo, void *val)
{
    printf("-----------signo is = %d\n", uinfo->si_signo);
    printf("-----------send pid = %u\n", uinfo->si_pid);
    printf("-----------sender's value is %d\n", uinfo->si_value);

    return ;
}

int main(void)
{
    pid_t pid = fork();

    union sigval uval;
    uval.sival_int = 887;

    if (pid > 0) {
        //int sigqueue(pid_t pid, int sig, const union sigval value);        
        sleep(1);
        sigqueue(pid, SIGUSR1, uval);   //kill 给子进程发信号 ,同时携带数据
        wait(NULL);

    } else if (pid == 0) {
        int n = 5;

        struct sigaction act;
        //void  (*sa_sigaction)(int, siginfo_t *, void *);
        act.sa_sigaction = func;
        sigemptyset(&act.sa_mask);
        act.sa_flags = SA_SIGINFO;    //sa_flags = 0;

        sigaction(SIGUSR1, &act, NULL);

        while (n--) {
            printf("I'm child pid = %d\n", getpid());
            sleep(1);
        }
    }

    return 0;
}
