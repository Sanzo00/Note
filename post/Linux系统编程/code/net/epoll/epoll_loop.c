#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <time.h>

#define MAX_EVENTS 1024
#define BUFLEN 4096
#define SERV_PORT 6666

void recvdata(int fd, int events, void *arg);
void senddata(int fd, int events, void *arg);

// 描述就绪文件描述符相关信息
struct myevent_s{
	int fd;
	int events;
	void *arg;											// 泛型指针
	void (*call_back)(int fd, int events, void *arg);	// 回调函数
	int status;											// 是否在监听 1->在红黑树上, 0->不在红黑树上
	char buf[BUFLEN];
	int len;
	long last_active;									// 记录每次加入红黑树上 g_efd 的时间值
};

int g_efd;												// 保存epoll_create返回的文件描述符
struct myevent_s g_events[MAX_EVENTS+1];				// 自定义结构体类型数组, +1->listenfd

// 初始化myevent_s 成员变量
void eventset(struct myevent_s *ev, int fd, void (*call_back)(int, int, void *), void *arg) {
	ev->fd = fd;
	ev->call_back = call_back;
	ev->events = 0;
	ev->arg = arg;
	ev->status = 0;
	// memset(ev->buf, 0, sizeof(ev->buf));
	// ev->len = 0;
	ev->last_active = time(NULL);
	return;
}

// 向epoll监听的红黑树插入文件描述符
void eventadd(int efd, int events, struct myevent_s *ev) {
	struct epoll_event epv = {0, {0}};
	int op;
	epv.data.ptr = ev;
	epv.events = ev->events = events;

	if (ev->status == 1) {
		op = EPOLL_CTL_MOD;
	}else {
		op = EPOLL_CTL_ADD;
		ev->status = 1;
	}

	if (epoll_ctl(efd, op, ev->fd, &epv) < 0) {
		printf("event add faild [fd=%d], events[%d]\n", ev->fd, events);
	}else {
		printf("event add OK [fd=%d], op = %d, events[%0X]\n", ev->fd, op, events);
	}
	return;
}

// 从epoll监听的红黑树删除文件描述符
void eventdel(int efd, struct myevent_s *ev) {
	struct epoll_event epv = {0, {0}};
	if (ev->status != 1) {
		return;
	}
	epv.data.ptr = ev;
	ev->status = 0;
	epoll_ctl(efd, EPOLL_CTL_DEL, ev->fd, &epv);
	return;
}

// 当文件描述符就绪, epoll返回, 调用函数与客户端建立连接
void acceptconn(int lfd, int events, void *arg) {
	struct sockaddr_in cin;
	socklen_t len = sizeof(cin);
	int cfd, i;

	if ((cfd = accept(lfd, (struct sockaddr *)&cin, &len)) == -1) {
		if (errno != EAGAIN && errno != EINTR) {
			// 出错处理
		}
		printf("%s: accept, %s\n", __func__, strerror(errno));
		return;
	}

	do{
		// 在g_events中为cfd找个位置存
		for (i = 0; i < MAX_EVENTS; ++i) {
			if(g_events[i].status == 0) {
				break;
			}
			if (i == MAX_EVENTS) {
				printf("%s: max connect limit[%d]\n", __func__, MAX_EVENTS);
				break;
			}
		}
		int flag = 0;
		if ((flag = fcntl(cfd, F_SETFL, O_NONBLOCK)) < 0) {
			printf("%s: fcntl nonblocking failed, %s\n", __func__, strerror(errno));
			break;
		}
		// 给cfd设置一个myevent_s的结构体, 回调函数设置为recvdata
		eventset(&g_events[i], cfd, recvdata, &g_events[i]);
		eventadd(g_efd, EPOLLIN, &g_events[i]);
	}while (0);
	
	printf("new connect [%s:%d][time:%ld], pos[%d]\n",
		inet_ntoa(cin.sin_addr), ntohs(cin.sin_port), g_events[i].last_active, i);
	return;
}

void recvdata(int fd, int events, void *arg) {
	struct myevent_s *ev = (struct myevent_s *) arg;
	int len;
	len = recv(fd, ev->buf, sizeof(ev->buf), 0);

	eventdel(g_efd, ev);				// 删除fd

	if (len > 0) {
		ev->len = len;
		ev->buf[len] = '\0';
		printf("C[%d]:%s\n", fd, ev->buf);

		// printf("send before set len = %d %s\n", ev->len, ev->buf);
		eventset(ev, fd, senddata, ev);	// 设置fd的回调函数为senddata
		// printf("send before add len = %d %s\n", ev->len, ev->buf);
		eventadd(g_efd, EPOLLOUT, ev);	// 将fd加到红黑树上, 监听写事件
	}else if(len == 0) {
		close(ev->fd);
		eventdel(g_efd, ev);
		printf("[fd=%d] pos[%ld] closed\n", fd, ev - g_events);
	}else {
		close(ev->fd);
		eventdel(g_efd, ev);
		printf("recv[fd=%d] error[%d]:%s\n", fd, errno, strerror(errno));
	}
	return;
}

void senddata(int fd, int events, void *arg) {
	struct myevent_s *ev = (struct myevent_s *) arg;
	int len;
	// printf("send len ======= %d, %s\n", ev->len, ev->buf);
	len = send(fd, ev->buf, ev->len, 0); // 将数据写回客户端
	if (len > 0) {
		printf("send[fd=%d], [%d]%s\n", fd, len, ev->buf);
		eventdel(g_efd, ev);			// 删除fd
		eventset(ev, fd, recvdata, ev);	// 修改fd为读事件
		eventadd(g_efd, EPOLLIN, ev);	// 向红黑树上插入fd的读事件
	}else {
		close(ev->fd);
		eventdel(g_efd, ev);
		printf("send[fd=%d] error %s\n", fd, strerror(errno));
	}
	return;
}

// 创建socket, 初始化lfd
void initlistensocket(int efd, short port) {
	int lfd = socket(AF_INET, SOCK_STREAM, 0);
	fcntl(lfd, F_SETFL, O_NONBLOCK); // 设置socket为非阻塞
	eventset(&g_events[MAX_EVENTS], lfd, acceptconn, &g_events[MAX_EVENTS]);
	eventadd(efd, EPOLLIN, &g_events[MAX_EVENTS]);

	struct sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(port);
	bind(lfd, (struct sockaddr *)&sin, sizeof(sin));
	listen(lfd, 20);
	return;
}

int main(int argc, char *argv[]) {
	unsigned short port = SERV_PORT;
	if (argc == 2) {
		port = atoi(argv[1]);
	}
	g_efd = epoll_create(MAX_EVENTS+1);	// 创建红黑树, g_efd
	if (g_efd <= 0) {
		printf("create efd in %s err %s\n", __func__, strerror(errno));
	}
	initlistensocket(g_efd, port);		// 初始化监听socket
	struct epoll_event events[MAX_EVENTS+1];	// 保存满足条件的就绪事件的文件描述符集合
	printf("server running:port[%d]\n", port);

	int checkpos = 0, i;
	while (1) {
		// 超时验证, 每次测试100个链接, 不测试listenfd.
		// 当客户端在60秒内没有和服务器通信, 关闭客户端的链接
		long now = time(NULL);
		for (i = 0; i < 100; ++i, ++checkpos) {
			if (checkpos == MAX_EVENTS) checkpos = 0;
			if (g_events[checkpos].status == 0) continue;

			long duration = now - g_events[checkpos].last_active; // 计算客户不活跃的时间
			if (duration >= 60) {
				close(g_events[checkpos].fd);					  // 关闭客户端的连接
				eventdel(g_efd, &g_events[checkpos]);			  // 将对应的文件描述符从红黑树上删除
				printf("[fd=%d] timeout\n", g_events[checkpos].fd);
			}
		}

		// 监听红黑树, 将满足的事件的文件描述符加到events数组中, 1秒没有事件满足返回0
		int nfd = epoll_wait(g_efd, events, MAX_EVENTS+1, 1000);
		if (nfd < 0) {
			printf("epoll wait error, exit\n");
			break;
		}

		for (i = 0; i < nfd; ++i) {
			struct myevent_s *ev = (struct myevent_s *)events[i].data.ptr;
			if ((events[i].events & EPOLLIN) && (ev->events & EPOLLIN)) { // 读事件
				ev->call_back(ev->fd, events[i].events, ev->arg);
			}
			if ((events[i].events & EPOLLOUT) && (ev->events & EPOLLOUT)) { // 写事件
				ev->call_back(ev->fd, events[i].events, ev->arg);
			}
		}
	}
	return 0;
}
