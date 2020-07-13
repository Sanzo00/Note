#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("./chdir path\n");
		exit(1);
	}
	int ret = chdir(argv[1]);
	if (ret == -1) {
		perror("chdir");
		exit(1);
	}
	int fd = open("chdir.txt", O_CREAT | O_RDWR, 0777);
	if (fd == -1) {
		perror("open");
		exit(1);
	}
	close(fd);
	char buf[256];
	getcwd(buf, sizeof(buf));
	printf("current dir: %s\n", buf);
	return 0;
}
