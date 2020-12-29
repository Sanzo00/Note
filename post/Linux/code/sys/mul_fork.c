#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("this is mul_fork.c\n");
    pid_t pid;
    int i;
    for (i = 0; i < 5; ++i) {
        pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(1);
        }else if (pid == 0) {
            break;
        }else {
            sleep(1);
        }
    }
    if (i < 5) {
        printf("I am %d child, pid = %u, ppid = %u\n", i, getpid(), getppid());
    }
    
    return 0;
}
