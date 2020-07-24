#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

typedef void (*sighandler_t) (int);

void catchsigint(int signo)
{
    printf("-----------------catch\n");
}

int main(void)
{
    sighandler_t handler;

    handler = signal(SIGINT, catchsigint);
    if (handler == SIG_ERR) {
        perror("signal error");
        exit(1);
    }

    while (1);
    
    return 0;
}
