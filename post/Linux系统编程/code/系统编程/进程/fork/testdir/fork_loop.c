#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int var = 100;

int main(void)
{
    pid_t pid;
    int i;

    for (i = 0; i < 5; i++) {
        pid = fork();
        if (pid == 0) {
            break;
        }
    }

    if (pid > 0) {  /*父进程*/ 
        sleep(i);
        var = 77;
        printf("I'm parent getpid = %u, var = %d\n", getpid(), var);

    } else if (pid == 0) {
        sleep(i);

        if (i == 1) {
            var = 500;
            printf("I'm %dth child getpid = %u, var = %d\n", i+1, getpid(),var);
            return 0;
        }
        printf("I'm %dth child getpid = %u, var = %d\n", i+1, getpid(),var);

    } else if (pid < 0) {
        perror("fork error");
        exit(1);
    }

    return 0;
}

