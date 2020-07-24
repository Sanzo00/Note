#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>

int main(void)
{
    int fd = open("./test.txt", O_RDWR);
    char *p;
    int i;

    struct stat sbuf;
    stat("./test.txt", &sbuf);
    int len = sbuf.st_size;
    printf("len = %d\n", len);
    
    p = mmap(NULL, len, PROT_READ|PROT_WRITE, MAP_PRIVATE, fd, 0);
    if (p == MAP_FAILED) {
        perror("mmap error");
        exit(1);
    }

    strcpy(p, "hehehe");  
    for (i = 0; i < len; i++) {
        printf("%c", p[i]);
    }
    printf("\n");

    munmap(p, len);
    close(fd);

    return 0;
}
