#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#define SERV_PORT 6666
#define SERV_IP "127.0.0.1"

int main() {
	int cfd, n;
	struct sockaddr_in serv_addr;
	socklen_t serv_addr_len;
	serv_addr_len = sizeof(serv_addr);
	// 创建socket
	cfd = socket(AF_INET, SOCK_STREAM, 0);
		
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, SERV_IP, &serv_addr.sin_addr.s_addr);
	// 链接服务器
	connect(cfd, (struct sockaddr *)&serv_addr, serv_addr_len);

	char buf[BUFSIZ];
	while (1) {
		fgets(buf, sizeof(buf), stdin);
		// 向服务端发送信息
		write(cfd, buf, strlen(buf));
		// 读取服务端发送的消息
		n = read(cfd, buf, sizeof(buf));
		write(STDOUT_FILENO, buf, n);
	}

	close(cfd);
	return 0;
}
