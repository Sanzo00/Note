#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
int main() {
    int fd = open("aa", O_RDWR);
    if (fd == -1) {
        perror("open file");
        exit(1);
    }
    // 文件大小
    int ret = lseek(fd, 0, SEEK_END);
    printf("file length = %d\n", ret);

    // 文件扩展
    ret = lseek(fd, 2000, SEEK_END);
    printf("file lingth = %d\n", ret);
    write(fd, "a", 1);
    close(fd);
}
