#include <stdio.h>
#include <stdlib.h>

int main() {
    char *val;
    const char *name = "AAA";
    int ret;
    // getenv
    val = getenv(name);
    printf("name = %s, val = %s\n", name, val);

    // setenv
    ret = setenv(name, "hello world", 1);
    if (ret == -1) {
        perror("setenv");
        exit(1);
    }

    val = getenv(name);
    printf("name = %s, val = %s\n", name, val);

    // unsetenv
    ret = unsetenv(name);
    if (ret == -1) {
        perror("AAA unsetenv");
        exit(1);
    }
    printf("name = %s, unsetenv = %d\n", name, ret);

    ret = unsetenv("BBB");
    if (ret == -1) {
        perror("BBB unsetenv");
        exit(1);
    }
    printf("name = %s, unsetenv = %d\n", "BBB", ret);

    return 0;
}
