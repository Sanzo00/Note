#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

char *buf[10];
int main() {
    int fd = open("hello", O_RDONLY);
    if (fd == -1) {
        perror("open");
    }
    
    int fd1 = open("newhello", O_WRONLY | O_CREAT, 0664);
    if (fd1 == -1) {
        perror("open1");
    }
    int len;
    while ((len = read(fd, buf, 10)) != 0) {
        if (len == -1) {
            perror("read");
            exit(1);
        }
        write(fd1, buf, len);
        printf("write bytes %d\n", len);
    }
    close(fd);
    close(fd1);
}
