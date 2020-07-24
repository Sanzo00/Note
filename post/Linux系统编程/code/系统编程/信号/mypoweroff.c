#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define SEC 5

void sig_int(int signo)
{
    system("sudo poweroff");
}

int main(void)
{
	struct sigaction act;		

	act.sa_handler = sig_int;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);		//不屏蔽任何信号
	sigaction(SIGALRM, &act, NULL);

    alarm(SEC);
    
    sleep(SEC);
    printf("-----------over-----------\n");

	return 0;
}
