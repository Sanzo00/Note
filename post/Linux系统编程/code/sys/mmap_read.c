#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
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
    struct STU student;
    struct STU *p;
    if (argc < 2) {
        printf("./mmap_read file_share_path");
        exit(1);
    }
    fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        sys_err("open");
    }
    p = mmap(NULL, sizeof(student), PROT_READ, MAP_SHARED, fd, 0);
    if (p == MAP_FAILED) {
        sys_err("mmap");
    }
    close(fd);

    while (1) {
        printf("id = %d, name = %s, sex = %c\n", p->id, p->name, p->sex);
        sleep(2);
    }
    munmap(p, sizeof(student));
    return 0;
}
