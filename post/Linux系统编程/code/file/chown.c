#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("./a.out filename uid gid\n");
        exit(1);
    }
    int uid = strtol(argv[2], NULL, 10);
    int gid = strtol(argv[3], NULL, 10);
    printf("uid = %d\n gid = %d\n", uid, gid);
    int ret = chown(argv[1], uid, gid);
    if (ret == -1) {
        perror("chown");
        exit(1);
    }
}
