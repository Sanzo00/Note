#include <unistd.h>
#include <stdio.h>

int main(void)
{
    pid_t pid;
    int i = 0, n = 5;

    for (i = 0; i < n; i++) {
        if (fork() == 0) {
            break;
        }
    }

    if (i == n) {
        sleep(i);
        printf("parnet pid = %d, parent pid = %d\n", getpid(), getppid());
    } else {
        sleep(i);
        printf(" %dth child pid = %d, parent pid = %d\n", i, getpid(), getppid());
    }

    return 0;
}
