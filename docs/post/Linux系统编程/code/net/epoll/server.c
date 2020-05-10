#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <sys/epoll.h>
#include <string.h>
#include <netinet/in.h>
#include <errno.h>
#include "wrap.h"
#define SERV_PORT 6666
#define MAXLINE 8000
#define OPEN_MAX 5000
int main() {
	int i, j, listenfd, connfd, sockfd;
	int n;
	ssize_t nready, efd, res;
	char buf[MAXLINE], str[INET_ADDRSTRLEN];
	socklen_t clilen;
	struct sockaddr_in cliaddr, servaddr;
	struct epoll_event tep, ep[OPEN_MAX];

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);
	int opt = 1;
	setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	Bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	Listen(listenfd, 128);
	// 创建epoll模型，edf指向红黑树的根节点
	efd = epoll_create(OPEN_MAX);
	if (efd == -1) {
		perror("epoll create");
		exit(1);
	}
	// listenfd为监听的读事件
	tep.events = EPOLLIN;
	tep.data.fd = listenfd;
	// 将listenfd插到epoll树上
	res = epoll_ctl(efd, EPOLL_CTL_ADD, listenfd, &tep);
	if (res == -1) {
		perror("epoll_ctl error");
		exit(1);
	}
	while (1) {
		nready = epoll_wait(efd, ep, OPEN_MAX, -1);
		if (nready == -1) {
			perror("epoll_wait error");
			exit(1);
		}
		for (i = 0; i < nready; ++i) {
			if (!(ep[i].events & EPOLLIN)) {
				continue;
			}
			if (ep[i].data.fd == listenfd) {
				clilen = sizeof(cliaddr);
				connfd = Accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);
				printf("reveived from %s at port %d\n", 
						inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)),
						ntohs(cliaddr.sin_port));
				tep.events = EPOLLIN;
				tep.data.fd = connfd;
				res = epoll_ctl(efd, EPOLL_CTL_ADD, connfd, &tep);
				if (res == -1) {
					perror("epoll_ctl error");
					exit(1);
				}
			}else {
				sockfd = ep[i].data.fd;
				n = Read(sockfd, buf, MAXLINE);
				if (n == 0) {
					res = epoll_ctl(efd, EPOLL_CTL_DEL, sockfd, NULL);
					if (res == -1) {
						perror("epoll_ctl error");
						exit(1);
					} 
					printf("client[%d] close connection\n", sockfd);
					Close(sockfd);
				} else if (n > 0) {
					for (j = 0; j < n; ++j) {
						buf[j] = toupper(buf[j]);
					}
					Writen(sockfd, buf, n);
					Writen(STDOUT_FILENO, buf, n);
				}else if (n < 0) {
					perror("read error");
					res = epoll_ctl(efd, EPOLL_CTL_DEL, sockfd, NULL);
					if (res == -1) {
						perror("epoll_ctl DEL error");
						exit(1);
					}
					Close(sockfd);
				}
			}
		}
	}


	return 0;
}
