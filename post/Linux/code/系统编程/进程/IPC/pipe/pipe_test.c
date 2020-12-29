#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    int fd[2];
    pid_t  pid;
    int i;

    int ret = pipe(fd);
    if (ret == -1) {
        perror("pipe error:");
        exit(1);
    }

    for (i = 0; i < 2; i++){
        pid = fork();
        if (pid == -1) {
            perror("pipe error:");  //ls | wc -l
            exit(1);
        }
        if (pid == 0)
            break;
    }

    if (i == 0) {  //兄  ls 
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        execlp("ls", "ls", NULL);
    } else if (i == 1) { // 弟 wc -l 
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        execlp("wc", "wc", "-l", NULL);
    } else if (i == 2) {  //父 
        close(fd[0]);
        close(fd[1]);
        for(i = 0; i < 2; i++)
            wait(NULL);
    }

    return 0;
}
