/*当执行SIGINT信号处理函数期间
 *多次收到SIGQUIT信号都将被屏蔽(阻塞)
 *SIGINT信号处理函数处理完，立刻解除对
 *SIGQUIT信号的屏蔽，由于没有捕捉该信号，
 *将立刻执行该信号的默认动作，程序退出
 */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sig_int(int signo)
{
	printf("catch signal SIGINT\n");
	sleep(10);			//模拟信号处理函数执行很长时间
	printf("end of handler\n");
}

int main(void)
{
	struct sigaction act;		


	act.sa_handler = sig_int;
	sigemptyset(&act.sa_mask);		
	sigaddset(&act.sa_mask, SIGQUIT);	

	/*将SIGQUIT加入信号屏蔽集,这就导致,在调用信号处理函数期间
	 *不仅不响应SIGINT信号本身,还不响应SIGQUIT*/
	act.sa_flags = 0;

	sigaction(SIGINT, &act, NULL);		//注册信号SIGINT捕捉函数

	while(1);

	return 0;
}
