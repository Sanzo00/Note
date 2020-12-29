#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

/*自定义的信号捕捉函数*/
void sig_int(int signo)
{
	printf("catch signal SIGINT\n");//单次打印
    sleep(10);
    printf("----slept 10 s\n");
}

int main(void)
{
	struct sigaction act;		

	act.sa_handler = sig_int;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);		//不屏蔽任何信号
    sigaddset(&act.sa_mask, SIGQUIT);

	sigaction(SIGINT, &act, NULL);

    printf("------------main slept 10\n");
    sleep(10);

	while(1);//该循环只是为了保证有足够的时间来测试函数特性

	return 0;
}
