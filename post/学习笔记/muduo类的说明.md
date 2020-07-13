# muduo 笔记

学习陈硕写的网络库[muduo](https://github.com/chenshuo/muduo)，照着实现了一遍，项目地址为[learn_muduo](https://github.com/Sanzona/learn_muduo).


## base库



### copyable、noncopyable

删除默认的拷贝构造和赋值来实现类的不可拷贝的属性。

```c
noncopyable(const noncopyable&) = delete;
void operator=(const noncopyable&) = delete;
```



### Atomic

Atomic是原子操作类，它是一个模板类，使用GCC提供的加减和逻辑原子操作来实现。

```c
private:
	volatile T value_;

// 原子比较和交换，先判断*ptr是否和oldval相等, 如果相等将值设置为newval
__sync_val_compare_add_swap(type *ptr, type oldval, newval);

// value_ += x;
__sync_fetch_and_add(&value_, x);

// value_ = newValue;
__sync_lock_test_and_set(&value_, newValue);
```

通过以上代码，封装自增、自减和赋值等原子操作。

Atomic的类模板定义在`namespace detail`中，在`namespace muduo`使用模板创建了两个类。

```c
typedef detail::AtomicIntegerT<int32_t> AtomicInt32;
typedef detail::AtomicIntegerT<int64_t> AtomicInt64;
```



### [Timestamp](https://github.com/Sanzona/learn_muduo/blob/master/muduo/base/Timestamp.cpp)

Timestamp使用微妙来计算时间，提供`toString`和格式化的接口，可以获取当前时间，返回一个对应的Timestamp对象，也可以返回一个

```c
static Timestamp now(); // 返回当前时间
static Timestamp invalid(); // 返回一个空对象
string toString() const; // 返回（秒.微妙）格式
string toFormattedString(bool showMicroseconds = true) const; // 格式化时间，年月日 时:分:秒.微妙
```

Timestamp继承`boost::less_than_comparable`，只需提供`<`的实现，自动实现`>`、`<=`、`>=`，继承`boost::equality_comparable`只需提供`==`自动实现`!=`。

```c
class Timestamp :  
	public boost::equality_comparable<Timestamp>,
	public boost::less_than_comparable<Timestamp>        
```

 跨平台，`int64_t`在32位系统是`long long int(%lld)`, 在64位系统是`long int(%ld)`

```c
printf("%" PRId64 "\n", value);
```



### [Date](https://github.com/Sanzona/learn_muduo/blob/master/muduo/base/Date.cpp)

使用`julianDayNumber`来计算年月日。距离公元前4713年1月1日的天数。和Timestamp类似，提供一些常用的接口。

```c
YearMonthDay getYearMonthDay(int julianDayNumber); // 获取对应的年月日
int getJulianDayNumber(int year, int month, int day)// 获取julian day
string Date::toIsoString(); // 格式化（年-月-日）
```

### [Mutex](https://github.com/Sanzona/learn_muduo/blob/master/muduo/base/Mutex.h)

Mutex封装锁，提供加锁解锁等操作。

```c
// 属性
pthread_mutex_t mutex_; // 定义一把锁
pid_t holder_;			// 记录加锁的线程ID
```

Mutex中一共有3个类：`MutexLock`、`UnassignGuard`、`MutexLockGuard`。

`MutexLock`使用`pthread_mutex_`函数封装初始化锁、加锁、解锁、销毁锁的操作。

`UnassignGuard`是`MutexLock`的内部类，他的特点是在构造函数中清除锁的持有者ID，析构的时候设置锁的持有者ID，这是供``Condition`的`wait()`使用。

`MutexLockGuard`采用RAII，构造的时候申请资源`lock`，析构的时候释放资源`unlock`，解放双手。



### [Condition](https://github.com/Sanzona/learn_muduo/blob/master/muduo/base/Condition.h)

`Condition`实现条件变量功能，使用`pthread_cond_`函数来封装`wait()`，`notify()`，`notifyAll`功能。也是采用RAII的机制，在构造中初始化条件变量`pcond_`，在析构函数中销毁条件变量。

`Condition`是`MutexLock`的友元，可以使用`MutexLock`的内部类`UnassignGuard`来实现`wait()`的功能。

`pthread_cond_wait`内部的机制时在线程进入阻塞前释放资源，当函数返回，重新持有锁。

```c
void wait()
{
    MutexLock::UnassignGuard ug(mutex_);
    int ret = pthread_cond_wait(&pcond_, mutex_.getPthreadMutex()); // 将线程添加到条件变量
    assert(ret == 0);
}
```



### [CountDownLatch](https://github.com/Sanzona/learn_muduo/blob/master/muduo/base/CountDownLatch.cpp)

倒计时类，将MutexLock和Condition封装在一起。

```c
mutable	MutexLock mutex_;
Condition 	condition_;
int 		count_;

void wait(); // 调用Condition等待
void countDown(); // 技术减1
int getCount(); // 获取当前的计数
```



### [Thread](https://github.com/Sanzona/learn_muduo/blob/master/muduo/base/Thread.cpp)

线程类，在namespace muduo中定义了ThreadNameInitializer类负责主线程的初始化操作，指定如果fork之后再之进程中执行after函数。

```c
ThreadNameInitializer()
{
    muduo::CurrentThread::t_threadName = "main";
    CurrentThread::tid();
    pthread_atfork(NULL, NULL, &afterFork);
}
```

设置ThreadData的结构体，保存线程的回调函数，名字，id，计数等信息。在ThreadData中定义了runInThread函数，用来执行回调函数。

线程执行的流程是：

- Thread构造，设置回调函数func_，默认CountDownLatch为1。

- pthread_create创建线程，绑定回调函数startThread，将ThreadData作为参数，创建成功之后主线程阻塞在latch_上，等待子线程的退出。
- 在startThread中调用ThreadData的runInThread函数
- latch_-1唤醒主线程，同时执行回调函数func\_，同时对异常进行处理。



### [CurrentThread](https://github.com/Sanzona/learn_muduo/blob/master/muduo/base/CurrentThread.cpp)

主线程类，提供stackTrace()用于查看堆栈的信息，同时包括线程的一些基本属性，id、名字等。



### [Exception](https://github.com/Sanzona/learn_muduo/blob/master/muduo/base/Exception.h)

异常处理类，继承std::exception，封装CurrentThread类的stackTrace()和重写what()方法。



### [BlockingQueue](https://github.com/Sanzona/learn_muduo/blob/master/muduo/base/BlockingQueue.h)

无界阻塞队列，底层是deque，利用条件变量实现一个生产者消费者模型，另外还有一个有界的阻塞队列（[BoundedBlockingQueue](https://github.com/Sanzona/learn_muduo/blob/master/muduo/base/BoundedBlockingQueue.h)），底层是circular_buffer。



### [StringPiece](https://github.com/Sanzona/learn_muduo/blob/master/muduo/base/StringPiece.h)

C++支持两种字符串：string和char*，当char\*传入函数，会构造一个临时的string变量，这就发生了内存的拷贝。StringPiece就是为了减少这种内存的拷贝，统一使用char\*记录字符串。重载了[]、等于、比较等操作。重载<<支持logged的使用。



### [LogStream](https://github.com/Sanzona/learn_muduo/blob/master/muduo/base/LogStream.cpp)

muduo的日志库采用C++的stream风格，有个好处是输出日志级别高于语句的日志级别的时候，打印是个空操作。muduo没有使用标准库中的iostream，而是自己封装的LogStream，不同于iostream，LogStream的<<操作是将数据放到缓冲区(FixedBuffer)中，外部程序可以重定向到任何文件中。



### [Logging](https://github.com/Sanzona/learn_muduo/blob/master/muduo/base/Logging.cpp)

日志类，muduo日志信息一共有5个级别，TRACE，DEBUG，INFO，WARN，ERROR，FATAL。通过宏定义创建Logger的临时对象，调用stream()函数返回LogStream对象。在Logging中定义了Impl类和SourceFile类，Impl类保存日志需要数据，SourceFile中LOG_函数所在的源文件和行号。



## net库

### [Endian](https://github.com/Sanzona/learn_muduo/blob/master/muduo/net/Endian.h)

提供字节序的转化。

本地字节序 <--> 网络字节序



### [InetAddress](https://github.com/Sanzona/learn_muduo/blob/master/muduo/net/InetAddress.cpp)

InetAddress是对sockaddr_in和sockaddr_in6的封装。

```c
// 设置本地端口
InetAddress(uint16_t port = 0, bool loopbackOnly = false, bool ipv6 = false);
// 设置一个指定的ip和端口
InetAddress(StringArg ip, uint16_t port, bool ipv6 = false);

sa_family_t family(); // 返回协议类型
string toIpPort() const; // 获取ip和port
string toIp() const; // 获取ip
uint16_t toPort() const; // 获取port
```



### [SocketsOps](https://github.com/Sanzona/learn_muduo/blob/master/muduo/net/SocketsOps.cpp)

封装对socket的常用操作。

```c
int createNonblockingOrDie(sa_family_t family); // 创建非阻塞的socket
int connect(int sockfd, const struct sockaddr* addr);
void bindOrDie(int sockfd, const struct sockaddr* addr);
void listenOrDie(int sockfd);
int accept(int sockfd, struct sockaddr_in6* addr); // 包含错误处理
void close(int sockfd);
void shutdownWrite(int sockfd);

void toIpPort(char* buf, size_t size, const struct sockaddr* addr); // 获取ip+port
void toIp(char* buf, size_t size, const struct sockaddr* addr); // 获取ip
// 根据ip和port得到对应的sockaddr_in
void fromIpPort(const char* ip, uint16_t port, struct sockaddr_in* addr);
void fromIpPort(const char* ip, uint16_t port, struct sockaddr_in6* addr);
// sockaddr和sockaddr_in(ip和端口分开存储)的转换
int getSocketError(int sockfd);
const struct sockaddr* sockaddr_cast(const struct sockaddr_in* addr);
const struct sockaddr* sockaddr_cast(const struct sockaddr_in6* addr);
struct sockaddr* sockaddr_cast(struct sockaddr_in6* addr);
const struct sockaddr_in* sockaddr_in_cast(const struct sockaddr* addr);
const struct sockaddr_in6* sockaddr_in6_cast(const struct sockaddr* addr);

struct sockaddr_in6 getLocalAddr(int sockfd);
struct sockaddr_in6 getPeerAddr(int sockfd);
bool isSelfConnect(int sockfd); // 判断子连接

ssize_t read(int sockfd, void *buf, size_t count);
ssize_t readv(int sockfd, const struct iovec *iov, int iovcnt);
ssize_t write(int sockfd, const void *buf, size_t count);
```



### [Socket](https://github.com/Sanzona/learn_muduo/blob/master/muduo/net/Socket.cpp)

Socket是对socket fd的封装，通过调用SocketsOps来实现。

```c
// 获取tcp的信息
bool getTcpInfo(struct tcp_info*) const;
bool getTcpInfoString(char* buf, int len) const;

void bindAddress(const InetAddress& localaddr); // 绑定地址
void listen(); // 监听湍口
int accept(InetAddress* peeraddr); // 获取连接
void shutdownWrite(); // 关闭写端而不是直接close

// TCP_NODELAY
void setTcpNoDelay(bool on);
// SO_REUSEADDR
void setReuseAddr(bool on);
// SO_REUSEPORT
void setReusePort(bool on);
// SO_KEEPALIVE
void setKeepAlive(bool on);
```

muduo在断开连接时，不是直接close socket，而是关闭写端，意味着还可以读，这样可以完整接受对方的数据。



### [Channel](https://github.com/Sanzona/learn_muduo/blob/master/muduo/net/Channel.h)

Channel类负责注册每个fd的事件回调函数，每个Channel只负责一个fd的事件分发，不拥有fd，不会在析构的时候关闭fd，Channel不是基类，不需要继承，一般作为其他类的成员。

### Poller

Poller是IO复用的封装，在muduo中是一个抽象基类，作为poll和epoll两种IO复用机制的父类。Poller是EventLoop的间接成员，只供owner EventLoop在IO线程中调用。poll返回之后，通过遍历pollfds_数组，找到对应的活动事件，复杂度O(n)，在Poller中有一个map<int, Channel*>的映射channels\_,

插入新的Channel的复杂度是O(logN)，更新已有的Channel的复杂度是O(1)，因为Channel记录了它的pollfds_数组中的下标，可以快速定位。删除Channel的复杂度也是O(n)。

### EventLoop

EventLoop中的loop不断的调用poll，来获取当前的活动事件，然后调用每个channel的handleEvent()方法，来处理事件。

EventLoop的runInLoop()函数，可以在IO线程中执行某个用户的任务回调，如果当前IO线程调用runInLoop()直接执行，否则放入到队列中等待执行，queueInLoop()，这样可以将TimerQueue的成员函数移动到其他IO线程，这样可以在不加锁的情况下保证线程安全。

IO线程一般阻塞在poll调用，为了让IO线程可以立即执行用户回调，muduo的做法是通过调用wakeup来唤醒IO线程，具体是向wakeupfd_中读写一个字节来实现，通过wakeup()和handleRead()对wakeupFd\_读写数据。

queuInLoop()的具体实现是，将cb放到队列中，在必要时唤醒IO线程，唤醒的条件有两个：调用queueInLoop的不是IO线程、正在执行队列中的回调函数doPendingFunctors()，原因是执行回调的函数有可能也会执行queueInLoop()，这样就要wakeup唤醒IO线程及时做处理，否则新添加的回调函数cb就不能及时被调用。



Reactor模型核心内容时序图。

![](C:/Users/na/Desktop/muduo/img/EventLoop.png)



### TimerQueue

TimerQueue定时器，一般通过select、poll的等待时间来实现定时，在muduo中使用timerfd，将对时间的处理和IO事件统一起来。

muduo的定时器由三个类：TimerId、Timer、TimerQueue。

TimerQueue的接口有addTimer()和cancel()，addTimer()是供EventLoop使用，EventLoop封装为更好用的runAt()、runAfter()、runEvery()。

TimerQueue使用set管理Timer，set中的key是pair<Timestamp,Timer*>，这样可以方便处理相同到期时间的Timer。

TimerQueue使用一个Channel来官差timerfd_上的可读事件。

TimerQueue目前有一个不理性的地方，Timer使用裸指针的方法管理，需要手动delete，在C++11中可以改为unique_ptr，避免手动释放资源。

通过TimerQueue的getExpired()来获取超时事件。

TimerQueue回调用户代码onTimer()的时序图。

![](C:/Users/na/Desktop/muduo/img/TimerQueue.png)



一次事件循环是从poll返回到再次调用poll阻塞。

循环中的各种回调发生的顺序。

![](C:/Users/na/Desktop/muduo/img/callback.png)



### Acceptor

Acceptor用于accept()新的TCP连接，通过回调函数通知使用者，供TcpServer使用，生命期由TcpServer控制。

成员函数包括Socket、Channel。Socket封装了socket文件描述符生命期，Channel用于观察socket上的可读事件，回调handleRead()，accept来接受新的连接，并回调用户的callback。



### TcpConnection

TcpConnection是唯一默认使用shared_ptr来管理的class，是muduo最复杂的class。

TcpConnection使用Channel来获取socket上的IO事件，自己处理可写事件，把可读事件通过MessageCallback传给用户，TcpConnection拥有Tcp socket，在析构中会close fd。

TcpConnection关闭连接的方式是被动关闭，对方先关闭连接，read返回0，触发关闭逻辑。

Tcp的关闭流程，X表示TcpConnection通常在这里析构。

![](C:/Users/na/Desktop/muduo/img/TcpConnection_close.png)

TcpConnection增加CloseCallback事件回调，提供给TcpServer和TcpClient使用，通知移除TcpConnectionPtr，普通用户使用ConnectionCallback。

TcpConnection的状态图。

![](C:/Users/na/Desktop/muduo/img/TcpConnection_status.png)



### Connector

socket是一次性的，一旦出错（对方拒绝连接），就无法恢复，只能重来。但是Connector是可以反复使用的，每次尝试连接都要使用新的socket文件描述符和新的Channel对象。

重试的间隔应该逐渐延长，例如0.5s、1s、2s、4s直到30秒，对于对象的生命期管理方面，如果使用EventLoop::runAfter()定时，而Connector在定时器到期之前析构了怎么办？可以在Connector的析构函数中注销定时器。

对于自连接的问题的处理，在发起连接时，首先在本地选择IP（由路由表确定）和随机选择端口，如果目标IP刚好是主机而且端口也相同，这就发生了自连接，处理办法就是断开连接重试。




### Buffer

muduo在读取数据时，采用cantter/gatherIO(分散聚集IO)，在一次系统调用可以对多个缓冲区进行输入输出，而且一部分的缓冲区来自stack，这样缓冲区足够大，通常一次readv调用就可以取完数据，

muduo采用的是水平触发，这样做不会丢失数据或消息，每次读取数据只需要一次系统调用，照顾了多个连接的公平性，不会因为某个连接上的数据量过大而影响其他连接处理消息。

发送数据的逻辑是，先尝试发送数据，如果只发送了部分数据，把剩余的数据放到outputBuffer_，开始关注writable事件，在handleWrite()中记录发送数据，如果outputBuffer\_中已经有待发送的的数据，就不能尝试发送，否则造成数据错乱。



### TcpServer

TcpServer用于处理新建TcpConnection。

TcpServer新建连接的函数调用。

![](C:/Users/na/Desktop/muduo/img/TcpServer.png)

TcpServer用来管理accpet获得的TcpConnection，供用户使用，生命期由用户控制。使用Accpetor获取新连接的fd，保存用户提供的ConnectionCallback和MessageCallback，在新建TcpConnection之后，将这两个回调函数传递给后者。

随机选择pool中的EventLoop，不允许TcpConnection在运行中更换EventLoop，每个TcpServer有自己的EventLoopThreadPool。



### TcpClient

TcpClient主要使用Connector来进行连接，Connector具备反复尝试连接的功能，因此客户端和服务端启动的顺序就无关紧要了。

连接断开后初次尝试连接应该具有随机性，如果服务端崩溃大量客户端重连，同时重连也会发生丢包，每个TcpClient应该	等待一段随机时间（0.5-2s）再尝试连接避免拥塞。

发起连接的时候如果发生TCP SYN丢包，那么系统默认的重试间隔是3s，职期间不会发生错误码。



### epoll

epoll是linux独有的高效的IO复用机制，它与poll的不同之处主要在于poll每次返回整个文件描述符数组，用户代码需要遍历数组以找到哪些文件描述符上有IO事件，epoll_wait()返回活动fd的列表，需要遍历的数组通常会小的多，再并发连接较大而活动连接比例不高时，epoll比poll更高效。

muduo定义Poller基类并提供两份实现PollPoller和EPollPoller。



### [HttpServer](https://github.com/Sanzona/learn_muduo/tree/master/muduo/net/http)

[HttpRequest](https://github.com/Sanzona/learn_muduo/blob/master/muduo/net/http/HttpRequest.h)封装了HTTP请求包的基本格式。

[HttpResponse](https://github.com/Sanzona/learn_muduo/blob/master/muduo/net/http/HttpResponse.h)封装了HTTP的响应包的基本格式。

[HttpContext](https://github.com/Sanzona/learn_muduo/blob/master/muduo/net/http/HttpContext.h)主要是对HTTP请求包的解析，将解析的结果存在对象HttpRequest中。

[HttpServer](https://github.com/Sanzona/learn_muduo/blob/master/muduo/net/http/HttpServer.h)封装了HTTP的对请求内容的响应，通过用户指定回调函数来处理请求，使用TcpServer来进行对连接进行处理。
