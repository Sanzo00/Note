#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <ctype.h>
#include "wrap.h"

#define SERV_PORT 6666

int main() {
	int i, j, n, maxi;
	// 自定义数组client，防止遍历1024个文件描述符
	int nread, client[FD_SETSIZE];
	int maxfd, listenfd, connfd, sockfd;
	// define INET_ADDRSTRLEN 16, IPV4在char表示的最大的长度
	char buf[BUFSIZ], str[INET_ADDRSTRLEN];
	struct sockaddr_in clie_addr, serv_addr;
	socklen_t clie_addr_len;
	fd_set rset, allset;

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(SERV_PORT);

	Bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	Listen(listenfd, 128);

	maxfd = listenfd;

	maxi = -1;
	for (i = 0; i < FD_SETSIZE; ++i) {
		client[i] = -1;
	}
	FD_ZERO(&allset);
	FD_SET(listenfd, &allset);

	while (1) {
		rset = allset;
		// 最大文件描述符+1，读文件描述符，写文件描述符， 异常文件描述符，等待时间
		nread = select(maxfd+1, &rset, NULL, NULL, NULL);
		if (nread < 0) {
			perror("select error");
			exit(1);
		}
		// 新的连接
		if (FD_ISSET(listenfd, &rset)) {
			clie_addr_len = sizeof(clie_addr);
			// Accept 不会阻塞
			connfd = Accept(listenfd, (struct sockaddr *)&clie_addr, &clie_addr_len);
			printf("receive from %s at port %d\n", 
					inet_ntop(AF_INET, &clie_addr.sin_addr, str, sizeof(str)),
					ntohs(clie_addr.sin_port));
			// 把Accept返回的文件描述符保存到clientp[]中
			for (i = 0; i < FD_SETSIZE; ++i) {
				if (client[i] < 0) {
					client[i] = connfd;
					break;
				}
			}
			if (i == FD_SETSIZE) {
				fputs("too many clients\n", stderr);
				exit(1);
			}
			FD_SET(connfd, &allset);
			if (connfd > maxfd) maxfd = connfd;
			if (i > maxi) maxi = i;
			if (--nread == 0) continue;
		}
		for (i = 0; i <= maxi; ++i) {
			if ((sockfd = client[i]) < 0) continue;
			if (FD_ISSET(sockfd, &rset)) {
				if ((n = Read(sockfd, buf, sizeof(buf))) == 0) { // 客户端关闭
					close(sockfd);
					FD_CLR(sockfd, &allset);
					client[i] = -1;
				}else if (n > 0) {
					for (j = 0; j < n; ++j) {
						buf[j] = toupper(buf[j]);
					}
					// sleep(5);
					Writen(sockfd, buf, n);
				}
				if (--nread == 0) break;
			}
		}
	}
	Close(listenfd);
	return 0;
}
