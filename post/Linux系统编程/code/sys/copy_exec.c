#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    int fd;
    fd = open("ps.log", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }else if (pid > 0) {
        sleep(1);
        printf("I am father\n");
    }else {
        dup2(fd, 1);
        execlp("ps", "ps", "-aux", NULL);
    }

    return 0;
}
