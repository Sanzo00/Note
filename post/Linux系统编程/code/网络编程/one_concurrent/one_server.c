#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <strings.h>
#define SERV_PORT 6666
int main() {

	int lfd, cfd, ret;
	struct sockaddr_in serv_addr, clie_addr;
	socklen_t clie_addr_len;
	char buf[BUFSIZ], clie_IP[BUFSIZ];
	int n, i;
	// 创建套接字
	lfd = socket(AF_INET, SOCK_STREAM, 0);
	if (lfd == -1) {
		perror("socket error");
		exit(1);
	}

	// 端口复用
	int opt = 1;
	setsockopt(lfd, SOCK_STREAM, SO_REUSEADDR, &opt, sizeof(opt));

	// 设置协议，ip和端口
	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	// 绑定端口
	ret = bind(lfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if (ret == -1) {
		perror("bind error");
		exit(1);
	}
	// 设置同时连接的数量
	ret = listen(lfd, 128);
	if (ret == -1) {
		perror("listen error");
		exit(1);
	}
	
	clie_addr_len = sizeof(clie_addr);
	// 阻塞等待客户端连接
	cfd = accept(lfd, (struct sockaddr *)&clie_addr, &clie_addr_len);
	if (cfd == -1) {
		perror("accept error");
		exit(1);
	}
	// 输出连接客户端的信息
	inet_ntop(AF_INET, &clie_addr.sin_addr.s_addr, clie_IP, sizeof(clie_IP));

	printf("client ip: %s, client port: %d\n", clie_IP, ntohs(clie_addr.sin_port));	
	while (1) {
		n = read(cfd, buf, sizeof(buf));
		for (i = 0; i < n; ++i) {
			buf[i] = toupper(buf[i]);
		}
		write(cfd, buf, n);
	}
	
	close(lfd);

	return 0;
}
