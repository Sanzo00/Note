#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    int fd = open("hello", O_RDWR);
    if (fd == -1) {
        perror("open");
        exit(1);
    }
    int fd1 = open("myhello", O_RDWR | O_CREAT, 0777);
    printf("fd1 = %d\n", fd1); 
    int ret = close(fd);
    printf("ret = %d\n", ret);
}
