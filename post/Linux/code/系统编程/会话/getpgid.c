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
        printf("child process PID == %d\n", getpid());                  //子进程ID
        printf("child Group ID == %d\n", getpgrp());                    //子进程所在组ID
        printf("child Group ID == %d\n", getpgid(0));                   //传0表当前进程
        printf("child Group ID == %d\n", getpgid(getpid()));
        exit(0);
    }

    sleep(3);

    printf("parent process PID == %d\n", getpid());
    printf("parent Group ID is %d\n", getpgrp());

    return 0;
}
