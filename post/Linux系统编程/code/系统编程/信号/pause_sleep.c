#include <stdio.h>
#include <signal.h>
#include <unistd.h>

/*所有信号处理函数的原型，都类此，
 *无返回值(void)，只有一个参数，表示信号编号*/
void sig_alrm(int signo)
{
	/*用来占位，可以不做任何事,但这个函数存在
	 *SIGALRM信号
	 *就不执行默认动作终止进程，而做其它事情*/
}

unsigned int mysleep(unsigned int sec)
{
	struct sigaction act, old;
	unsigned int unslept;			//保存未休眠够的时间

	act.sa_handler = sig_alrm;
	sigemptyset(&act.sa_mask);		//清空
	act.sa_flags = 0;
	sigaction(SIGALRM, &act, &old);	//注册信号处理函数sig_alrm
									//同时要保存旧的处理方式

	alarm(sec);						//设置sec秒闹钟
	pause();			//进程阻塞,收到一个信号后,pause返回-1,解除阻塞

	unslept = alarm(0);	//取消旧的定时器,将剩余时间保存
	/*
	 *正常情况下，闹钟到sec秒后发送SIGALRM信号，
	 *pause函数收到信号，调用信号处理函数sig_alrm
	 *pause函数返回，此时定时器已经到时，
	 *执行unslept=alarm(0)不起作用，unslept为0
	 
	 *如果是异常情况下，定时器还没到sec秒，
	 *pause函数被别的信号唤醒，需要将定时器取消
	 *定时器返回剩余时间，也就是未休眠够的时间
	 */

	sigaction(SIGALRM, &old, NULL);	//恢复SIGALRM信号原来的处理方式
	/*因为是在实现库函数,有可能用户之前设置过SIGALRM信号的处理方式*/

	return unslept;
}

int main(void)
{
	while(1){
		mysleep(5);
		printf("Five seconds passed\n");
	}

	return 0;
}
