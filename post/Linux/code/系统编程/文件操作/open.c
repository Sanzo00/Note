#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    
	// 打开文件
	int fd = open("hello", O_RDWR);
    
	// 判断是否成功
	if (fd == -1) {
        perror("open");
        exit(1);
    }


    // 创建新的文件
	int newfd = open("myhello", O_RDWR | O_CREAT, 0666);
    
	printf("fd = %d\n", newfd); 
    
	// 关闭文件
	int ret = close(newfd);

	if (ret == -1) perror("close失败");
}
