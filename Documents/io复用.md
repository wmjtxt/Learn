I/O复用: select, poll, epoll
====

I/O复用典型使用在下列网络应用场合。
* 当客户处理多个描述符时，必须使用I/O复用。
* 一个客户同时处理多个套接字是可能的，不过比较少见。
* 如果一个TCP服务器既要处理监听套接字，又要处理连接套接字，一般就要使用I/O复用。
* 如果一个服务器既要处理TCP，又要处理UDP，一般就要使用I/O复用。
* 如果一个服务器要处理多个服务或者多个协议，要使用I/O复用。
I/O复用并非只限于网络编程，许多重要的应用程序也需要使用这项技术。

# 5种I/O模型
Unix提供了五种不同的I/O模型：
* 阻塞式I/O；
* 非阻塞式I/O；
* I/O复用（select,poll,epoll）；
* 信号驱动式I/O（SIGIO）；
* 异步I/O（POSIX的aio\_系列函数）。
默认为阻塞式I/O模型，它也是最常用的I/O模型。

# 各种I/O模型的比较
前四种为同步I/O模型，第一阶段不同，第二阶段均相同:在数据从内核复制到调用者的缓冲区期间，进程阻塞于recvfrom调用。
异步I/O模型在这两个阶段都要处理，从而不同于其他4种模型。
//上面两句话有歧义啊。
POSIX把这两个术语定义如下：
* 同步I/O操作导致请求进程阻塞，直到I/O操作完成。
* 异步I/O操作不导致请求进程阻塞。

# 1.select
select的用途：在一段指定时间内，监听用户感兴趣的文件描述符上的可读、可写和异常等事件。
```c
#include <sys/select.h>
int select(int nfds, fd_set* readfds, fd_set* writefds, fd_set* exceptfds, struct timeval* timeout);
```
其中：
* nfds参数指定被监听的文件描述符的总数。
* readfds,writefds,exceptfds参数分别指向可读、可写和异常等事件对应的文件描述符。
* timeout参数用来设置select函数的超时时间。如果timeout传递NULL，则select将一直阻塞，直到某个文件描述符就绪。

# 2.poll
poll系统调用和select类似，也是在指定时间内轮询一定数量的文件描述符，以测试其中是否有就绪者。poll的原型如下：
```
#include <poll.h>
int poll(struct pollfd* fds, nfds_t nfds, int timeout);
```
* fds参数是一个pollfd结构类型的数组，它指定所有我们感兴趣的文件描述符上发生的可读、可写和异常等事件。pollfd结构体的定义如下：
```
struct pollfd
{
    int fd;         //文件描述符
    short events;   //注册的事件
    short revents;  //实际发生的事件，由内核填充
};
```

# 3.epoll
epoll是linux特有的I/O复用函数。它在实现和使用上与select、poll有很大差异。
* 首先，epoll使用一组函数来完成任务，而不是单个函数。
* 其次，epoll把用户关心的文件描述符上的事件放在内核里的一个事件表中，从而无须像select和poll那样每次调用都要重复传入文件描述符集或事件集。
* 但epoll需要使用一个额外的文件描述符，来唯一标示内核中的这个事件表。
* 这个文件描述符使用epoll_create函数来创建：
```
#include <sys/epoll.h>
int epoll_create(int size);
```
size参数现在不起作用,只是给内核一个提示，告诉它事件表需要多大。
* epoll_ctl用来操作epoll的内核事件表。
* epoll系列系统调用的主要接口是epoll_wait函数。

* epoll对文件描述符的操作有两种模式：LT和ET
    * LT（Level Trigger，电平触发）模式是默认的工作模式，在这种模式下epoll相当于一个效率较高的poll。
    * ET（Edge Trigger，边沿触发）模式是epoll的高效工作模式。


|系统调用|select|poll|epoll|
|:------:|:----:|:--:|:---:|
|事件集合|用户通过3个参数分别传入感兴趣的可读、可写及异常等事件，内核通过对这些参数的在线修改来反馈其中的就绪事件。这使得用户每次调用select都要重置这3个参数|统一处理所有事件类型，因此只需一个事件集参数。用户通过pollfd.events传入感兴趣的事件，内核通过修改pollfd.revents反馈其中就绪的事件|内核通过一个事件表直接管理用户感兴趣的所有事件。因此每次调用epoll_wait时，无须反复传入用户感兴趣的事件。epoll_wait系统调用的参数events仅用来反馈就绪的事件|
|应用程序索引就绪文件描述符的时间复杂度|O(n)|O(n)|O(1)|
|最大支持文件描述符数|一般有最大值限制，1024或2048|65535|65535|
|工作模式|LT|LT|支持ET高效模式|
|内核实现和工作效率|采用轮询方式来检测就绪事件，算法时间复杂度为O(n)|采用轮询方式来检测就绪事件，算法时间复杂度为O(n)|采用回调方式来检测就绪事件，算法时间复杂度为O(1)|
