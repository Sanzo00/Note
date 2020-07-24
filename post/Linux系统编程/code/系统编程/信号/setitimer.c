#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

unsigned int my_alarm(unsigned int sec)
{
	struct itimerval it, oldit;
    int ret;

	it.it_value.tv_sec = sec;
	it.it_value.tv_usec = 0;
	it.it_interval.tv_sec = 0;
	it.it_interval.tv_usec = 0;

	ret = setitimer(ITIMER_REAL, &it, &oldit);
    if (ret == -1) {
        perror("setitimer");
        exit(1);
    }
	return oldit.it_value.tv_sec;
}

int main(void)
{
	int i;
	my_alarm(1);  //alarm(sec);

	for(i = 0; ; i++)
		printf("%d\n", i);

	return 0;
}
