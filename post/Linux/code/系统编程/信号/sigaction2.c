/*自动屏蔽本信号，调用完毕后屏蔽自动解除*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

/*自定义的信号捕捉函数*/
void sig_int(int signo)
{
	printf("catch signal SIGINT\n");
	sleep(10);			//模拟信号处理函数执行很长时间
	printf("end of handler\n");
}

int main(void)
{
	struct sigaction act, old;		

	act.sa_handler = sig_int;
	sigemptyset(&act.sa_mask);		//依然不屏蔽任何信号
	act.sa_flags = 0;

	sigaction(SIGINT, &act, &old);	//注册信号处理函数

	while(1);

	sigaction(SIGINT, &old, NULL);	//注册信号处理函数

	return 0;
}
