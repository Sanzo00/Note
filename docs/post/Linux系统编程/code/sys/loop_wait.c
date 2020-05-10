#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() { 
    pid_t pid, wpid;
    int i;
    for (i = 0; i < 3; ++i) {
        pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(1);
        }else if(pid == 0) {
            break;
        }
    }
    if (i < 3) {
        sleep(i);
        printf("I am %d child, pid = %d, ppid = %d\n", i, getpid(), getppid());
    }else{
        sleep(i);
        printf("I am father, pid = %d\n", getpid());
        // 阻塞回收所有进程
        //while ((wpid = waitpid(-1, NULL, 0)) > 0) { // 等价于 wait(NULL)
        //    printf("child pid = %d exit\n", wpid);
        //}
        
        // 轮训回收所有的子进程
        int cnt = 0;
        do {
            wpid = waitpid(-1, NULL, WNOHANG);
            if (wpid > 0) {
                printf("child pid = %d exit\n", wpid);
                cnt++;
            }
            // 参数为WNOHANG且子进程没有退出, 返回0
            sleep(1);
        }while (cnt != 3);
    }

    return 0;
}
