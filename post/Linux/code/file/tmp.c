#include <stdlib.h>
#include <stdio.h>

int main() {
    char *buf = "0644";
    int ret = strtol(buf, NULL, 8);
    printf("ret = %d\n", ret);
}
