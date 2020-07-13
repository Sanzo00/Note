#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main() {
	pid_t pid;
	if ((pid = fork()) < 0) {
		perror("fork");
		exit(1);
	}else if (pid == 0) {
		printf("child process is %d\n", getpid());
		printf("group ID of child is %d\n", getpgid(0));
		printf("session ID of child is %d\n", getpgid(0));
		
		sleep(3);
		
		setsid();
		printf("changed:\n");
		printf("child process is %d\n", getpid());
		printf("group ID of child is %d\n", getpgid(0));
		printf("session ID of child is %d\n", getpgid(0));

		sleep(3);
		exit(0);
	}

	return 0;
} 
