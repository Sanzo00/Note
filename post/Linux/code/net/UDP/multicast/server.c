#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <net/if.h>

#define SERVER_PORT 6666
#define CLIENT_PORT 7777
#define MAXLINE 1500
#define GROUP "239.0.0.2"

int main() {
	int sockfd;
	struct sockaddr_in serveraddr, clientaddr;
	char buf[MAXLINE] = "kali@root\n";
	struct ip_mreqn group;
	
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	bzero(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVER_PORT);

	bind(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
	// 设置组地址
	inet_pton(AF_INET, GROUP, &group.imr_multiaddr);
	// 指定本机地址
	inet_pton(AF_INET, "0.0.0.0", &group.imr_address);
	// 获取eth0对应网卡的编号
	group.imr_ifindex = if_nametoindex("eth0");

	// 组播权限
	setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_IF, &group, sizeof(group));

	bzero(&clientaddr, sizeof(clientaddr));
	clientaddr.sin_family = AF_INET;
	inet_pton(AF_INET, GROUP, &clientaddr.sin_addr.s_addr);
	clientaddr.sin_port = htons(CLIENT_PORT);

	int i = 0;
	while (1) {
		sprintf(buf, "kali@root %d\n", ++i);
		sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)&clientaddr, sizeof(clientaddr));
		sleep(1);
	}
	
	close(sockfd);
	return 0;
}
