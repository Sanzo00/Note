#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }else if (pid > 0) {
        wpid = wait(&status);
        printf("wpid = %d\n", wpid);
        if (wpid == -1) {
            perror("wait");
            exit(1);
        }
        if (WIFEXITED(status)) { // 正常退出
            // 获取退出值
            printf("child exit with %d\n", WEXITSTATUS(status));
        }

        if (WIFSIGNALED(status)) { // 非正常退出
            // 获取信号值
            printf("child killed by %d\n", WTERMSIG(status));
        }
        while (1) {
            sleep(1);
            printf("I am father, pid = %d\n", getpid());
        }
    }else {
        printf("I am child, pid = %d, ppid = %d\n", getpid(), getppid());
        // int a = 10 / 0;
        
        // char *s = "asdada";
        // s[1] = 'a';
        
        execl("seg", "seg", NULL);

        sleep(3);
        exit(1);
    }

    return 0;
}
