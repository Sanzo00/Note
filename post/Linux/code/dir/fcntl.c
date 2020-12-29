#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd;
    int flag;
    char *buf = "桃花坞里桃花庵, 桃花庵下桃花仙";
    char *buf1 = "桃花仙人种桃树, 又摘桃花买酒钱";
    // open file
    fd = open("test.txt", O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }
    
    if (write(fd, buf, strlen(buf)) == -1) {
        perror("write");
        exit(1);
    }
    
    flag = fcntl(fd, F_GETFL, 0);
    if (flag == -1) {
        perror("fcntl");
        exit(1);
    }
    // 添加文件状态: 追加
    flag |= O_APPEND;
    if (fcntl(fd, F_SETFL, flag) == -1) {
        perror("fcntl -- append write");
        exit(1);
    }

    if (write(fd, buf1, strlen(buf1)) == -1) {
        perror("write again");
        exit(1); 
    }
    close(fd);

    return 0;
}
