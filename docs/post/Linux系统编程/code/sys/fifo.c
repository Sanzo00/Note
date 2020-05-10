#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main() {
    if (mkfifo("pp", 0666) < 0 && errno != EEXIST) {
        perror("mkfifo");
        exit(1);
    }
    pid_t pid;
    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(1);
    }else if (pid == 0) { // 读
        int fd = open("pp", O_RDONLY);
        char buf[1024];
        int len = read(fd, buf, sizeof(buf));
        write(STDOUT_FILENO, buf, len);
        close(fd);
    }else { // 写
        int fd = open("pp", O_WRONLY);
        char *buf = "hello world\n";
        write(fd, buf, strlen(buf));
        close(fd);
    }
    return 0;
}
