#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

void mydaemon() {
	pid_t pid = fork();
	if (pid == -1) {
		perror("fork");
		exit(1);
	}else if (pid > 0) exit(1);

	setsid();
	int ret = chdir("/");
	if (ret == -1) {
		perror("chdir error");
		exit(1);
	}
	umask(0002);
	close(STDIN_FILENO);
	open("/dev/null", O_RDWR);
	dup2(0, STDOUT_FILENO);
	dup2(0, STDERR_FILENO);
}
int main() {
	mydaemon();
	while (1);
	return 0;
	return 0;
}
