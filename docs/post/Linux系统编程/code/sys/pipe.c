#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];// 0读, 1写
    int ret;
    pid_t pid;

    ret = pipe(fd);
    if (ret == -1) {
        perror("pipe");
        exit(1);
    }
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }else if (pid == 0) { // write
        close(fd[0]);
        char *buf = "hello world\n";
        write(fd[1], buf, strlen(buf));
    }else { // read
        close(fd[1]);
        char buf[1024];
        for (int i = 0; i < 1024; ++i) {
            buf[i] = 'x';
        }
        ret = read(fd[0], buf, sizeof(buf));
        write(STDOUT_FILENO, buf, ret);
        buf[ret] = 0;
        printf("read: %s", buf);
    }

    return 0;
}
