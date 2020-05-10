#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid;
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }else if(pid > 0) {
        sleep(1);    
        printf("I am father, pid = %d, ppid = %d\n", getpid(), getppid());
    }else {
        printf("I am child,  pid = %d, ppid = %d\n", getpid(), getppid());
        sleep(3);
        printf("I am child,  pid = %d, ppid = %d\n", getpid(), getppid());
    }
    return 0;
}
