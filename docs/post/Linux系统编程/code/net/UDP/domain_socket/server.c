#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <stddef.h>

#include "wrap.h"

#define SERV_ADDR "serv.socket"

int main() {
	int lfd, cfd, len, size, i;
	struct sockaddr_un servaddr, cliaddr;
	char buf[BUFSIZ];
	
	lfd = Socket(AF_UNIX, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sun_family = AF_UNIX;
	strcpy(servaddr.sun_path, SERV_ADDR);
	
	/*
		offsetof(type, member)
		((int) &( (type*)0 )->member )
	*/
	len = offsetof(struct sockaddr_un, sun_path) + strlen(servaddr.sun_path);
	
	// 确保Bind之前不存在文件, Bind创建文件
	unlink(SERV_ADDR);
	// 参数3不是sizeof(servaddr)
	Bind(lfd, (struct sockaddr *)&servaddr, len);
	
	Listen(lfd, 20);

	printf("Accept ...\n");
	while (1) {
		len = sizeof(cliaddr);
		cfd = Accept(lfd, (struct sockaddr *)&cliaddr, (socklen_t *)&len);
		
		// 获取客户端socket文件名的长度
		len -= offsetof(struct sockaddr_un, sun_path);
		cliaddr.sun_path[len] = '\0';

		printf("client bind filename %s\n", cliaddr.sun_path);

		while ((size = read(cfd, buf, sizeof(buf))) > 0) {
			for (i = 0; i < size; ++i) {
				buf[i] = toupper(buf[i]);
			}
			write(cfd, buf, size);
		}
		close(cfd);
	}
	return 0;
}
