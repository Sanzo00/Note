#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>
#include <fcntl.h>

int main() {
    int fd = open("test.txt", O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("open");
        exit(1);
    }
    int ret = truncate("test.txt", 4);
    if (ret == -1) {
        perror("truncate");
        exit(1);
    }
    char *p = NULL;
    p = mmap(NULL, 4, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if (p == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }
    strcpy(p, "hel\n");
    
    ret = munmap(p, 4);
    if (ret == -1) {
        perror("munmap");
        exit(1);
    }
    close(fd);

    return 0;
}
