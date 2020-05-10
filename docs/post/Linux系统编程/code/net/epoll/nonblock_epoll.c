#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>

#define MAXLINE 10
#define SERV_PORT 6666
#define SERV_IP "127.0.0.1"

int main() {
	struct sockaddr_in servaddr, cliaddr;
	socklen_t cliaddr_len;
	int listenfd, connfd;
	char buf[BUFSIZ];
	char str[INET_ADDRSTRLEN];
	int efd, flag;
	
	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET, SERV_IP, &servaddr.sin_addr.s_addr);
	// servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);
	
	bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	listen(listenfd, 20);

	cliaddr_len = sizeof(cliaddr);
	connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &cliaddr_len);
	printf("receive from %s port %d\n", 
			inet_ntop(AF_INET, &cliaddr.sin_family, str, sizeof(str)),
			ntohs(cliaddr.sin_port));

	// 修改connfd为非阻塞读
	flag = fcntl(connfd, F_GETFL);
	flag |= O_NONBLOCK;
	fcntl(connfd, F_SETFL, flag);

	struct epoll_event event;
	struct epoll_event resevent[10];
	int res, len;
	
	efd = epoll_create(10);
	event.events = EPOLLIN | EPOLLET;
	event.data.fd = connfd;

	epoll_ctl(efd, EPOLL_CTL_ADD, connfd, &event);
	while (1) {
		printf("epoll_wait...\n");
		res = epoll_wait(efd, resevent, 10, -1);
		printf("epoll_wait end res %d\n", res);

		if (resevent[0].data.fd == connfd) {
			while ((len = read(connfd, buf, MAXLINE/2)) > 0) {
				write(STDOUT_FILENO, buf, len);
			}
		}
	}

	return 0;
}
