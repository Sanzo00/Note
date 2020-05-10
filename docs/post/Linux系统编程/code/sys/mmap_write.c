#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>

struct STU{
    int id;
    char name[20];
    char sex;
};

void sys_err(char *str) {
    perror(str);
    exit(1);
}

int main(int argc, char *argv[]) {
    int fd;
    struct STU student = {10, "sanzo", 'M'};
    struct STU *p;

    if (argc < 2) {
        printf("./a.out file_shared_path\n");
        exit(1);
    }
    fd = open(argv[1], O_RDWR|O_CREAT, 0644);
    ftruncate(fd, sizeof(student));
    p = mmap(NULL, sizeof(student), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if (p == MAP_FAILED) {
        sys_err("mmap");
    }
    close(fd);
    while (1) {
        memcpy(p, &student, sizeof(student));
        student.id++;
        sleep(1);
    }
    munmap(p, sizeof(student));
    return 0;
}
