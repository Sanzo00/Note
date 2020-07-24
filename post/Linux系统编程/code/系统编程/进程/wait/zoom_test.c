#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid, wpid;
    pid = fork();
    int status;
    
    if (pid == 0) {
            printf("---child, my parent= %d, going to sleep 10s\n", getppid());
            sleep(20);
            printf("-------------child die--------------\n");
            exit(77);
    } else if (pid > 0) {
        while (1) {
            printf("I am parent, pid = %d, myson = %d\n", getpid(), pid);

            wpid = wait(&status);
            if (wpid == -1) {
                perror("wait error");
                exit(1);
            }

            if (WIFEXITED(status)) {  //为真说明子进程正常结束
                printf("child exit with %d\n", WEXITSTATUS(status));
            } else if (WIFSIGNALED(status)) { //为真说明子进程被信号终止（异常）
                printf("child is killed by %d\n", WTERMSIG(status));
            }

            sleep(1);
        }
    } else {
        perror("fork");
        return 1;
    }

    return 0;
}
