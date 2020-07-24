#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;

    if ((pid = fork()) < 0) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        printf("child PID == %d\n",getpid());
        printf("child Group ID == %d\n",getpgid(0)); // 返回组id
        //printf("child Group ID == %d\n",getpgrp()); // 返回组id
        sleep(7);
        printf("----Group ID of child is changed to %d\n",getpgid(0));
        exit(0);

    } else if (pid > 0) {
        sleep(1);
        setpgid(pid,pid);           //让子进程自立门户,成为进程组组长,以它的pid为进程组id

        sleep(13);
        printf("\n");
        printf("parent PID == %d\n", getpid());
        printf("parent's parent process PID == %d\n", getppid());
        printf("parent Group ID == %d\n", getpgid(0));

        sleep(5);
        setpgid(getpid(),getppid()); // 改变父进程的组id为父进程的父进程
        printf("\n----Group ID of parent is changed to %d\n",getpgid(0));

        while(1);
    }

    return 0;
}
