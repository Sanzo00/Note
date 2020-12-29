#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() 
{
	int fd = open("english.txt", O_RDWR);
	if (fd == -1) perror("open");

	// 获取文件大小
	int len = lseek(fd, 0, SEEK_END);
	printf("english.txt length is %d\n", len);

	// 扩展文件大小
	len = lseek(fd, 10, SEEK_END);
	printf("english.txt length is %d\n", len);

	write(fd, "add", 3);

	close(fd);

	return 0;
}
