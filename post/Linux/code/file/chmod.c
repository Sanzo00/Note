#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("./a.out filename 0644\n");
        exit(1);
    }

    int val = strtol(argv[2], NULL, 8);
    printf("%s %d\n", argv[2], val);
    int ret = chmod(argv[1], val);
    if (ret == -1) {
        perror("chmod");
        exit(1);
    }
}
