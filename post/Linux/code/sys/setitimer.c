#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

unsigned int my_alarm(unsigned int sec) {
    struct itimerval it, oldit;
    it.it_value.tv_sec = sec;
    it.it_value.tv_usec = 0;
    it.it_interval.tv_sec = 0;
    it.it_interval.tv_usec = 0;

    int ret = setitimer(ITIMER_REAL, &it, &oldit);
    if (ret == -1) {
        perror("setitimer");
        exit(1);
    } 
    return oldit.it_value.tv_sec;
}


int main() {
    my_alarm(1);
    for (int i = 0; ; ++i) {
        printf("%d\n", i);
    }
    return 0;
}
