#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void printped(sigset_t *ped)
{
    int i;
    for (i = 1; i < 32; i++) {
        if (sigismember(ped, i) == 1) {
            putchar('1');
        } else {
            putchar('0');
        }
    }
    printf("\n");
}
int main(void)
{
    sigset_t myset, oldset, ped;
    sigemptyset(&myset);
    sigaddset(&myset, SIGQUIT);
    sigprocmask(SIG_BLOCK, &myset, &oldset);
    while (1) {
        sigpending(&ped);
        printped(&ped);
        sleep(1);
    }

    return 0;
}
