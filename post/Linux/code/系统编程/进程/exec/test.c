#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

extern char **envrion;

int main(void)
{
    char *argvv[] = {"ls", "-l", NULL};

    //execl("/bin/ls", "ls", "-l", NULL);
    //execlp("ls", "ls", "-l", NULL);
    execv("/bin/ls", argvv);

    perror("exec");
    exit(1);

    return 0;
}
