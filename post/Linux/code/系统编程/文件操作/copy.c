#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {

	int src = open("english.txt", O_RDWR);
	int dst = open("copy_enlish.txt", O_RDWR | O_CREAT, 0644);

	if (src == -1 | dst == -1) {
		perror("open");
	}

	char buf[1024];

	int rd = 0;
	while ((rd = read(src, buf, sizeof(buf))) > 0) {
		write(dst, buf, rd);
	}

	close(src);
	close(dst);

	return 0;
}
