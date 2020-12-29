#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    int fd = open("tmpfile", O_CREAT | O_RDWR, 0644);
    if (fd == -1) {
        perror("open");
        exit(1);
    }
    // 删除临时文件, 等到fd关闭才真正删除
    int ret = unlink("tmpfile");
    
    // 写文件
    write(fd, "hello\n", 6);
    lseek(fd, 0, SEEK_SET);

    // 读文件
    char buf[1024] = {0};
    int len = read(fd, buf, sizeof(buf));
	
    // 输出到屏幕
    write(1, buf, len);

    close(fd);
    return 0;
}
