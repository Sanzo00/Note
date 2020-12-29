#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define SERV_PORT 6666
#define SERV_IP "127.0.0.1"
int main() {
	int cfd, i;
	struct sockaddr_in serv_addr;
	socklen_t servaddr_len;
	servaddr_len = sizeof(serv_addr);

	cfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, SERV_IP, &serv_addr.sin_addr.s_addr);

	connect(cfd, (struct sockaddr *)&serv_addr, servaddr_len);

	char buf[BUFSIZ];
	char ch = 'a';
	while (1) {
		for (i = 0; i < 5; ++i) {
			buf[i] = ch;
		}
		buf[i-1] = '\n';
		ch++;
		for (; i < 10; ++i) {
			buf[i] = ch;
		}
		buf[i-1] = '\n';
		ch++;
		write(cfd, buf, 10);
		sleep(2);
		int len = read(cfd, buf, sizeof(buf));
		write(STDOUT_FILENO, buf, len);
	}
	return 0;
}
