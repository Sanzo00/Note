#ifndef __QQ_IPC_H_
#define __QQ_IPC_H_
//0 新用户注册
//1 聊天信息
//2 服务器更新列表信息
struct usr {
	int num;
	char name[10];
	pid_t pid;
};

struct c_msg {
	int num;
	struct usr src;
	struct usr dest;
	char msg[256];
};

struct s_msg {
	int num;
	struct usr info;
};

#endif
