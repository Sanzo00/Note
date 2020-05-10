#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
const int n = 5;
int main() {
    int i;
    pid_t pid, tpid;
    for (i = 0; i < n; ++i) {
        pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(1);
        }
        if (pid == 0) {
            break;   
        }
        if (i == 2) tpid = pid; 
    } 
    if (i < n) {
        while (1) {
            printf("I am child %d, pid = %d\n", i, pid);
            sleep(1);
        }
    }else if (i == n) {
        sleep(1);
        kill(tpid, SIGKILL);
        printf("pid = %d is dead\n", tpid);
    }
    return 0;
}


