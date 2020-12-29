#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;
    printf("main getpid = %u\n", getpid());
    printf("main getppid = %u\n", getppid());
    int i;

    for (i = 0; i < 5; i++) {
        pid = fork();
        if (pid == 0) {
            break;
        }
    }

    if (pid > 0) {  /*父进程*/ 
        printf("fork parent getpid = %u\n", getpid());
        printf("fork parent getppid = %u\n", getppid());
    } else if (pid == 0) {
        printf("child getpid = %u\n", getpid());
        printf("child getppid = %u\n", getppid());
    } else if (pid < 0) {
        perror("fork error");
        exit(1);
    }

    printf("================\n");

    return 0;
}

