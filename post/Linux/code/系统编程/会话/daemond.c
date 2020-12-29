#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

void mydaemond(void)
{
    pid_t pid = fork();
    if (pid > 0) {
        exit(1);
    }

    setsid();

    int ret = chdir("/home/itcast/");
    if (ret == -1) {
        perror("chdir error");  // chdir error no such diractroy or file
        exit(1);
    }

    umask(0022);

    //close(fd[0]);  //stdin
    close(STDIN_FILENO);
    open("/dev/null", O_RDWR);
    dup2(0, STDOUT_FILENO);
    dup2(0, STDERR_FILENO);
}

int main(void)
{
    mydaemond();

    while (1) {
        
    }

    return 0;
}
