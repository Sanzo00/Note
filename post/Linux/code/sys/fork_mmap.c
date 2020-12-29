#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/wait.h>

int var = 100;
int main() {
    int *p = NULL;
    pid_t pid;
    int fd;

    fd = open("temp", O_RDWR|O_CREAT|O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        exit(1);
    }
    unlink("temp"); // 删除临时文件的目录项, 当使用文件的进程退出后就会自动删除
    ftruncate(fd, 4);
    p = (int*) mmap(NULL, 4, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if (p == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }
    close(fd); // 映射区建立之后, 可直接关闭文件

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }else if (pid == 0) {
        *p = 1000;
        var = 200;
        printf("child, *p = %d, var = %d\n", *p, var);
        exit(1);
    }else {
        sleep(1);
        printf("father, *p = %d, var = %d\n", *p, var);
        wait(NULL);
        int ret = munmap(p, 4);
        if (ret == -1) {
            perror("munmap");
            exit(1);
        }
    }

    return 0;
}
