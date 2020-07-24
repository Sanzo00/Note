#include <stdio.h>
#include <unistd.h>

int main(void)
{
    pid_t pid = fork();

    if (pid > 0) {
        execl("/home/itcast/0105_Linux/process_test/exec/output", "output", NULL);
    } else if (pid == 0) {
        printf("i'm parent pid = %d\n", getpid());
    }

    return 0;
}
