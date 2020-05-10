#include <stdio.h>
#include "head.h"
int main() {
    int ret1 = sum(1, 1);
    printf("main\n");
    int ret2 = sub(1, 1);
    printf("%d %d\n", ret1, ret2);
}
