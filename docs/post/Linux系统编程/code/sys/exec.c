#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid;
    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(1);
    }else if (pid > 0) {
        sleep(2); 
        printf("I am father\n");
    }else {
        // execlp("ls", "ls", "-l", "-a", NULL);
        // execl("/bin/ls", "ls", "-l", "-a", NULL);
        char *argv[] = {"ls", "-l", "-a", NULL};
        execv("/bin/ls", argv);
    }

    return 0;
}
