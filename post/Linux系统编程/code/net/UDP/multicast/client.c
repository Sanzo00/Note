#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <net/if.h>

#define SERVER_PORT 6666
#define CLIENT_PORT 7777
#define GROUP "239.0.0.2"

int main() {
	struct sockaddr_in localaddr;
	int confd;
	ssize_t len;
	char buf[BUFSIZ];

	struct ip_mreqn group;

	confd = socket(AF_INET, SOCK_DGRAM, 0);
	
	bzero(&localaddr, sizeof(localaddr));
	localaddr.sin_family = AF_INET;
	inet_pton(AF_INET, "0.0.0.0", &localaddr.sin_addr.s_addr);
	localaddr.sin_port = htons(CLIENT_PORT);
	
	bind(confd, (struct sockaddr *)&localaddr, sizeof(localaddr));

	// 设置组播地址
	inet_pton(AF_INET, GROUP, &group.imr_multiaddr);
	// 将本地IP添加到组播组中
	inet_pton(AF_INET, "0.0.0.0", &group.imr_address);
	// 获取网卡编号
	group.imr_ifindex = if_nametoindex("eth0");

	// 设置权限
	setsockopt(confd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &group, sizeof(group));

	while (1) {
		len = recvfrom(confd, buf, sizeof(buf), 0, NULL, 0);
		write(STDOUT_FILENO, buf, len);
	}
	close(confd);

	return 0;
}
