#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#define N 5
int main(void)
{
    int i;
    pid_t pid, q;

    raise(SIGSEGV);
    abort();


    for (i = 0; i < N; i++) {
        pid = fork();
        if (pid == 0)
            break;
        if (i == 2)
            q = pid;
    }
    if (i < 5) {
        while(1) {
            printf("I'm child %d, getpid = %u\n", i, getpid());
            sleep(1);
        }

    } else {
        sleep(1);
        kill(q, SIGKILL);
        while (1);
    }

    return 0;
}








#if 0
int main(void)
{
	int i;				//默认创建5个子进程

	for(i = 0; i < N; i++)	//出口1,父进程专用出口
		if(fork() == 0)
			break;			//出口2,子进程出口,i不自增

    if (i == 3) {
        sleep(1);
        printf("-----------child ---pid = %d, ppid = %d\n", getpid(), getppid());
        kill(getppid(), SIGKILL);

    } else if (i == N) {
        printf("I am parent, pid = %d\n", getpid());
        while(1);
    }

	return 0;
}
#endif 
