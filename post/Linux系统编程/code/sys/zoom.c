#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid;
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }else if(pid == 0) {
        printf("I am child, pid = %d, ppid = %d\n", getpid(), getppid());
        sleep(4);    
        printf("I am child, i gona dead\n");
    }else {
        while (1) {
            sleep(1);
            printf("I am father, pid = %d, ppid = %d\n", getpid(), getppid());
        }
    }
    return 0;
}
