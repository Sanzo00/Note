#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "qq_ipc.h"

int main(void)
{

	//1.打开公共fifo，阻塞等待读
    
	//2.读到内容字符串解析
    
	//3.判断协议号num
    
		//1，用户注册
			//非阻塞写打开新用户创建的私有FIFO
			//增加在线列表节点
            
		//2. 用户聊天
			//取出dst
			//中转数据给客户
            
        //3. 用户退出
            //将用户从在线列表中摘除
            
	//返回第一步1,继续阻塞在公共FIFO读等待
    
}
