#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd = open("a.txt", O_RDWR);
    if (fd == -1) {
        perror("a.txt open");
        exit(1);
    }

    int fd1 = open("b.txt", O_RDWR);
    if (fd1 == -1) {
        perror("b.txt open");
        exit(1);
    }

    printf("a.txt fd = %d\n", fd);
    printf("b.txt fd = %d\n", fd1);
	
    // 把fd复制到fd1           
    int ret = dup2(fd, fd1);
    if (ret == -1) {
        perror("dup2");
        exit(1);
    }
    printf("current fd1 = %d\n", fd1);
	printf("ret = %d\n", ret);

    char *buf = "dup2222222222222222222222222\n";
    write(fd, buf, strlen(buf));
    write(fd1, "hello world\n", 12);
    close(fd);
    close(fd1);

    return 0;
}
