#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

void sys_err(char *str){
    perror(str);
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc < 5) {
        perror("./copy filename start end");
        exit(1);
    }
    int fd;
    char *p = NULL;
    int fd = open(argv[1], O_RDWR);
    if (fd == -1) sys_err("open");
    int l = strtol(argv[3], NULL, 10);
    int r = strtol(argv[4], NULL, 10);
    int len = r - l + 1;
    p = mmap(NULL, len, PROT_READ|PROT_WRITE, MAP_SHARED,fd, l);
    if (p == MAP_FAILED) sys_err("mmap");
    close(fd);
    
    fd = open(argv[2], O_CREAT|O_WRONLY, 0644);
    if (fd == -1) sys_err("open");
    lseek(fd, l, SEEK_SET);
    
    

    return 0;
}
