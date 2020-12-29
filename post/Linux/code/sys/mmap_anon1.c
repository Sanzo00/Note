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
    int fd = open("/dev/zero", O_RDWR);
    p = (int*) mmap(NULL, 4, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0); // 使用字符文件
    if (p == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

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
