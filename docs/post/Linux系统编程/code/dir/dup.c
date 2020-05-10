#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd = open("a.txt", O_RDWR);
    if (fd == -1) {
        perror("open");
        exit(1);
    }
    printf("file fd = %d\n", fd);
    // 返回最小的文件描述符
    int ret = dup(fd);
    if (ret == -1) {
        perror("dup");
        exit(1);
    }
    printf("dup fd = %d\n", ret);
    char *buf = "hello world\n";
    char *buf1 = "hi world\n";
    // fd, ret指向同一个文件, 位置同步
    write(fd, buf, strlen(buf));
    write(ret, buf1, strlen(buf1));
    close(fd);
    return 0;
}
