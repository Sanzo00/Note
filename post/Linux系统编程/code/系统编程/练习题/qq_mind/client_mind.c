#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "qq_ipc.h"

int main(int argc, char *argv[])
{
	//1.获取自己的pid和name，填充struct s_msg
    
	//2.非阻塞属性创建私有FIFO
    
	//3.打开服务器公共的FIFO,把自己的信息向服务器注册
    
	//4.非阻塞读私有FIFO
		//read返回-1，继续轮询
		//read返回>0, 协议包解析
			//num为1, 聊天信息解析,打印到输出端聊天信息
			//num为2，服务器更新在线列表信息,打印到输出端
            
	//4.设置标准输入为非阻塞属性，读标准输入
		//read返回-1，继续轮询
		//read返回>1,字符串解析，填充struct c_msg
		//向服务器公共FIFO,写msg
       
    //5.轮询
}
