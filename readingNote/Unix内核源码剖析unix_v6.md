Unix内核源码剖析 青柳隆宏
====

Unix V6, 1975, 贝尔实验室; PDP-11


* 基本功能
    * 管理运行中的程序（进程）
    * 内存管理
    * 文件系统
    * 文件和周边设备共享I/O
    * 中断
    * 支持终端处理

* PDP-11
    * PSW(Processor Status Word): 处理器状态字，16位
|比特位|含义|
|15~14|处理器当前模式(00:内核模式,11:用户模式)|
|13~12|处理器先前模式(00:内核模式,11:用户模式)|
|7-5|处理器优先级（7~0）|
|4|陷入（trap）位|
|3|N。负位。指令执行结果为负时置1|
|2|Z。零位。指令执行结果为0时置1|
|1|V。溢出位。指令执行中发生溢出时置1|
|0|C。借位位。指令执行中发生进位或借位时置1|

# 进程

* 进程的状态: 可执行状态，休眠状态
* 处理器具有两种模式：用户模式和内核模式，通过PSW能够在两者间切换 
* 切换模式时，映射到虚拟地址空间的物理内存区域也随之发生变换。
* 进程的状态信息和控制信息由proc结构体和user结构体管理。每个进程都包含一组proc和user结构体
* proc结构体
    * proc结构体常驻内存。
    * proc结构体管理着在进程状态、执行优先级等与进程相关的信息中需要经常被内核访问的那部分信息。
    ```c
    struct proc
    {
        char p_stat;
        char p_flag;
        char p_pri;
        char p_sig;
        char p_uid;
        char p_time;
        char p_cpu;
        char p_nice;
        char p_ttyp;
        char p_pid;
        char p_ppid;
        char p_addr;
        char p_size;
        char p_wchan;
        char *p_textp;
    }proc[NPROC];
    /* stat codes */
    #define SSLEEP  1
    #define SWAIT   1
    #define SRUN    1
    #define SIDL    1
    #define SZOMB   1

    /* flag codes */
    #define SLOAD   01
    #define SSYS    02
    #define SLOCK   04
    #define SSWAP   010
    #define STRC    020
    #define SWTED   040
    ```
    表2-1 proc结构体
    |成员|含义|
    |-|-|
    |p_stat|状态。等于NULL时意味着proc[]数组中该元素为空。|
    |p_flag|标志变量。参见表2-3|
    |p_pri|执行优先级。数值越小优先级越高，下次被执行的可能性也就越大|
    |p_sig|接收到的信号|
    |p_uid|用户ID(整数)|
    |p_time|在内存或交换空间内存在的时间(秒)|
    |p_cpu|占用CPU的累计时间（时钟tick数）|
    |p_nice|用来降低执行优先级的补正系数。缺省值是0，通过系统调用nice可以设置成用户希望的数值|
    |p_ttyp|正在操作进程的终端|
    |p_pid|进程ID|
    |p_ppid|父进程ID|
    |p_addr|数据段的物理地址(单位为64字节)|
    |p_size|数据段的长度（单位为64字节）|
    |p_wchan|使进程进入休眠状态的原因|
    |*p_textp|使用的代码段（text segment）|
    表2-2 进程的状态
    |状态|含义|
    |-|-|
    |SSLEEP|高优先级休眠状态。执行优先级为负值|
    |SWAIT|低优先级休眠状态。执行优先级为0或正值|
    |SRUN|可执行状态|
    |SIDL|进程生成中|
    |SZOMB|僵尸状态|
    |SSTOP|等待被跟踪|
    表2-3 进程的标志常量
    |SLOAD|进程图像处于内存中（未被换出至交换空间）|
    |SSYS|系统进程，不会被换出至交换空间。在UNIX V6中只有proc[0]是系统进程|
    |SLOCK|进程调度锁。不允许进程图像被换出至交换空间|
    |SSWAP|进程图像已被换出至交换空间。由于被换出至交换空间，user.u_rsav[]的值不再有效。必须从user.u_ssav[]中恢复r5、r6的值|
    |STRC|处于被跟踪状态|
    |SWTED|在被跟踪时使用|

* user结构体
    * user结构体有可能被移交至交换空间
    * user结构体用来管理进程打开的文件或目录信息。
    * 内核只需要当前进程的user结构体，因此当进程被换出至交换空间时，对应的user结构体也会被移出内存。
    
    代码清单2-3 user结构体（user.h）
    ```c
    struct user
    {
        int u_rsav[2];
        int u_fsav[25];
        char u_segflg;
        char u_error;
        ...
    };
    ```

