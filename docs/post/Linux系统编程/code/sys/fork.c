#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    printf("this is fork.c\n");

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(1);
    }else if(pid > 0) {
        printf("I am father, pid = %d, ppid = %d\n", getpid(), getppid());
        sleep(1);
    }else {
        printf("I am child, pid = %d, ppid = %d\n", getpid(), getppid());
    }
    printf("bye\n");

    return 0;
}
