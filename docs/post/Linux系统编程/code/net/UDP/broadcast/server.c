#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SERVER_PORT 6666
#define MAXLINE 1500
#define BROADCAST_IP "192.168.154.255"
#define CLIENT_PORT 7777

int main() {
	int sockfd;
	struct sockaddr_in serveraddr, clientaddr;
	char buf[BUFSIZ];

	// 构造UDP的套接字
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	bzero(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVER_PORT);
	
	bind(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));

	int flag = 1;
	// 设置套接字广播权限
	setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &flag, sizeof(flag));
	
	//设置client地址, IP+port 192.168.154.255+7777
	bzero(&clientaddr, sizeof(clientaddr));
	clientaddr.sin_family = AF_INET;
	inet_pton(AF_INET, BROADCAST_IP, &clientaddr.sin_addr.s_addr);
	clientaddr.sin_port = htons(CLIENT_PORT);

	int i = 0;
	while (1) {
		sprintf(buf, "Drink %d glasses of water\n", ++i);
		// fgets(buf, sizeof(buf), stdin);
		int ret = sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)&clientaddr, sizeof(clientaddr));
		if (ret == -1) {
			perror("sendto error");
			exit(1);
		}
		sleep(1);
	}

	close(sockfd);

	return 0;
}
