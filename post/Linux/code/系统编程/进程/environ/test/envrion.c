#include <stdio.h>

extern char **environ;  //本质：char *envron[] = {"HOME=/home/itcat", "SHELL=/bin/bash", ....}

int main(void)
{
    int i = 0;

    for (i = 0; environ[i] != NULL; i++) {
        printf("%s\n", environ[i]);
    }

    return 0;
}
