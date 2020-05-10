#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <strings.h>
#include <ctype.h>
#include "wrap.h"
#include <sys/wait.h>
#include <pthread.h>
#define SERV_PORT 8888

struct s_info{
	struct sockaddr_in addr;
	int cfd;
};

void *do_work(void *arg) {
	int n, i;
	struct s_info *ts = (struct s_info*) arg;
	char buf[BUFSIZ], clie_IP[BUFSIZ];
	while (1) {
		n = Read((*ts).cfd, buf, sizeof(buf));
		if (n == 0) {
			return 0;
		}else if(n < 0) {
			perror("read error");
			exit(1);
		}else {
			for (i = 0; i < n; ++i) {
				buf[i] = toupper(buf[i]);
			}
			printf("client IP: %s, client port: %d\n", 
			inet_ntop(AF_INET, &(*ts).addr.sin_addr.s_addr, clie_IP, sizeof(clie_IP)),
			ntohs((*ts).addr.sin_port));
			
			write(STDOUT_FILENO, buf, n);
			write((*ts).cfd, buf, n);
		}
	}
}

int main() {
	int lfd, cfd;
	struct sockaddr_in serv_addr, clie_addr;
	socklen_t clie_addr_len;
	lfd = Socket(AF_INET, SOCK_STREAM, 0);
	pthread_t tid;
	struct s_info ts[256];
	int i = 0;

	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	// inet_pton(AF_INET, "192.168.1.101", &serv_addr.sin_addr.s_addr);
	Bind(lfd, (struct scockaddr *)&serv_addr, sizeof(serv_addr));

	Listen(lfd, 128);
	
	while (1) {
		clie_addr_len = sizeof(clie_addr);
		cfd = Accept(lfd, (struct sockaddr *)&clie_addr, &clie_addr_len);
		ts[i].addr = clie_addr;
		ts[i].cfd = cfd;
		
		pthread_create(&tid, NULL, do_work, (void*)&ts[i]);
		pthread_detach(tid);
		++i;
	}
	return 0;
}
