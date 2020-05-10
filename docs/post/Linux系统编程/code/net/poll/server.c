#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <poll.h>
#include <string.h>
#include <netinet/in.h>
#include <errno.h>
#include "wrap.h"
#define SERV_PORT 6666
#define MAXLINE 80
#define OPEN_MAX 1024
int main() {
	int i, j, maxi, listenfd, connfd, sockfd;
	int nready;
	ssize_t n;
	
	char buf[BUFSIZ], str[INET_ADDRSTRLEN];
	socklen_t clien;
	struct pollfd client[OPEN_MAX];
	struct sockaddr_in servaddr, clieaddr;

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);
	// 设置端口复用
	int opt = 1;
	setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	Bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	Listen(listenfd, 128);

	client[0].fd = listenfd;
	client[0].events = POLLIN;
	for (i = 1; i < OPEN_MAX; ++i) {
		client[i].fd = -1;
	}
	maxi = 0;
	while (1) {
		// 阻塞监听是否有新的链接请求
		nready = poll(client, maxi+1, -1);
		if (client[0].revents & POLLIN) {
			clien = sizeof(clieaddr);
			connfd = Accept(listenfd, (struct sockaddr *)&clieaddr, &clien);
			printf("received from %s at PORT %d\n",
					inet_ntop(AF_INET, &clieaddr.sin_addr, str, sizeof(str)),
					ntohs(clieaddr.sin_port));
			// 把Accept返回的connfd，放到client[]中
			for (i = 1; i < OPEN_MAX; ++i) {
				if (client[i].fd < 0) {
					client[i].fd = connfd;
					break;
				}
			}
			
			if (i == OPEN_MAX) {
				perror("too many clients");
				exit(1);
			}
			// 监听新连接的客户端的读时间
			client[i].events = POLLIN;
			// 更新client[]中的最大下标
			if (i > maxi) maxi = i;
			// 判断时候有读写事件
			if (--nready == 0) continue;
		}

		// 找到对应的客户端，处理请求
		for (i = 1; i <= maxi; ++i) {
			if ((sockfd = client[i].fd) < 0) {
				continue;
			}

			if (client[i].revents & POLLIN) {
				if ((n = Read(sockfd, buf, MAXLINE)) < 0) {
					// 连接重置
					if (errno == ECONNRESET) {
						printf("client[%d] aborted connection\n", i);
						Close(sockfd);
						client[i].fd = -1;
					}else {
						perror("read error");
						exit(1);
					}
				}else if (n == 0) {
					printf("client[%d] closed connection\n", i);
					Close(sockfd);
					client[i].fd = -1;
				}else {
					for (j = 0; j < n; ++j) {
						buf[j] = toupper(buf[j]);
					}
					Writen(sockfd, buf, n);
				}
				if (--nready == 0) break;
			}
		}
	}
	return 0;
}
