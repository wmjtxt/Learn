深入理解计算机系统 Computer Systems : A Programmer's Perspective(Third Edition)
====


# 目录
- [0 全书概览](#0-全书概览)
- [1 计算机系统漫游](#1-计算机系统漫游)
- [2 信息的表示和处理](#2-信息的表示和处理)
- [3 程序的机器级表示](#3-程序的机器级表示)
    * [3.1 历史观点](##31-历史观点)
        * [表 3.1 Intel处理器历史](###表-31-Intel处理器历史)
    * [3.2 程序编码](##32-程序编码)
        * [3.2.2 代码示例](###322-代码示例)
    * [3.3 数据格式](##33-数据格式) * [3.4 访问信息](##34-访问信息)
        * [表3.3 寄存器](###表33-寄存器)
        * [3.4.1 操作数指示符](###341-操作数指示符)
        * [3.4.2 数据传送指令](###342-数据传送指令)
        * [3.4.3 数据传送示例](###343-数据传送示例)
        * [3.4.4 压入和弹出栈数据](###344-压入和弹出栈数据)
- []()

# 0 全书概览
全书共12章，旨在阐述计算机系统的核心概念。
* 第1章：计算机系统漫游。这一章通过研究“hello, world”这个简单程序的生命周期，介绍计算机系统的主要概念和主题。
* 第2章：信息的表示和处理。讲述了计算机的算术运算，重点描述了会对程序员有影响的无符号数和数的补码表示的特性。
* 第3章：程序的机器级表示。教读者如何阅读由C编译器生成的x86-64机器代码。

# 1 计算机系统漫游

# 2 信息的表示和处理 

# 3 程序的机器级表示

第3章总结起来就三个字：学汇编。基本目标是能够阅读和理解汇编代码，终极目标是能通过阅读汇编代码来优化程序。
书中是基于x86-64来讲解的，所以开头介绍了一下Intel处理器的历史。见表3.1。摩尔定律其实有点牵强，就像墨菲定律一样。
3.2节从命令gcc讲起，算是步入正题。3.3讲了数据格式。3.4寄存器。3.5算术和逻辑操作。3.6控制，包括条件和循环。3.7过程，
包括运行时栈和递归等。3.8数组分配和访问。3.9异质的数据结构。3.10控制和数据交互。3.11浮点代码。

## 3.1 历史观点

### 表 3.1 Intel处理器历史

|处理器|年份|晶体管数量|具体介绍|
|-|-|-|-|
|8086|1978|29K||
|80826|1982|134K||
|i386|1985|275K||
|||||
|||||
|Core i7, Haswell|2013|1.4G||

## 3.2 程序编码

```
linux> gcc -Og -o p p1.c p2.c
```
其中，-Og告诉编译器使用会生成符合原始C代码整体结构的机器代码的优化等级。

gcc调用了一整套程序。包括：
* 1.C预处理器扩展源代码，插入所有用#include命令指定的文件，并扩展所有用`#define`声明指定的宏。
* 2.编译器产生两个源文件的汇编代码，p1.s和p2.s
* 3.汇编器将汇编代码转换成二进制目标代码文件p1.o和p2.o
* 4.链接器将两个目标代码文件与实现库函数（如printf）的代码合并，并产生最终的可执行文件p。

### 表3.2 gcc命令常用选项

|选项|含义|其他|
|-|-|-|
|-o|||
|-E|||
|-S|||
|-g|||
|-c|||

### 3.2.2 代码示例

```
long mult2(long, long);

void multstore(long x, long y, long *dest){
    long t = mult2(x,y);
    *dest = t;
}
```

### 旁注：展示程序的字节表示

```
(gdb) x/14xb mulstore
```

### objdump命令

OBJDUMP可以用来查看机器代码文件的内容。执行方式如下：

```
linux> objdump -d mstore.o
```

## 3.3 数据格式

## 3.4 访问信息

### 表3.3 寄存器

对应书中p120的图3-2

|63|31|15|7|含义|
|-|-|-|-|-|
|`%rax`|`%eax`|`%ax`|`%al`|返回值|
|`%rbx`|`%ebx`|`%bx`|`%bl`|被调用者保存|
|`%rcx`|`%ecx`|`%cx`|`%cl`|第4个参数|
|`%rdx`|`%edx`|`%dx`|`%dl`|第3个参数|
|`%rsi`|`%esi`|`%si`|`%sil`|第2个参数|
|`%rdi`|`%edi`|`%di`|`%dil`|第1个参数|
|`%rbp`|`%ebp`|`%bp`|`%bpl`|被调用者保存|
|`%rsp`|`%esp`|`%sp`|`%spl`|栈指针|
|`%r8`|`%r8d`|`%r8w`|`%r8b`|第5个参数|
|`%r9`|`%r9d`|`%r9w`|`%r9b`|第6个参数|
|`%r10`|`%r10d`|`%r10w`|`%r10b`|调用者保存|
|`%r11`|`%r11d`|`%r11w`|`%r11b`|调用者保存|
|`%r12`|`%r12d`|`%r12w`|`%r12b`|被调用者保存|
|`%r13`|`%r13d`|`%r13w`|`%r13b`|被调用者保存|
|`%r14`|`%r14d`|`%r14w`|`%r14b`|被调用者保存|
|`%r15`|`%r15d`|`%r15w`|`%r15b`|被调用者保存|

### 3.4.1 操作数指示符

操作数分为三种类型 : 立即数、寄存器、内存引用。

表3.4 操作数格式
|类型|格式|操作数值|名称|
|-|-|-|-|
|立即数|$Imm|Imm|立即数寻址|
|寄存器|ra|R[ra]|寄存器寻址|
|存储器|Imm|M[Imm]|绝对寻址|
|存储器|(ra)|M[R[ra]]|间接寻址|
|存储器|Imm(rb)|M[Imm+R[rb]]|(基址+偏移量)寻址|
|存储器|(ra,ri)|M[R[rb]+R[ri]]|变址寻址|
|存储器||||
|存储器||||
|存储器||||
|存储器||||

### 3.4.2 数据传送指令
### 3.4.3 数据传送示例
### 3.4.4 压入和弹出栈数据

x86-64中, 栈向下增长, 因此入栈时栈顶地址-8, 出栈时站定地址+8:
* 将一个四字值压入栈中，首先将栈指针减8，然后将值写到新的栈顶地址，因此，指令`pushq %rbp`等价于如下两个指令：
    * `subq $8,%rsp`
    * `movq %rbp,(%rsp)`
* 弹出一个四字的操作包括从栈顶位置读出数据，然后将栈指针加8, `popq %rax`等价于
    * `movq (%rsp),%rax`
    * `addq $8,%rsp`

|指令|效果|描述|
|-|-|-|
|`pushq S`|`R[%rsp]<-R[%rsp]-8;`<br>`M[R[%rsp]]<-S`|将四字压入栈|
|`pushq S`|`D<-M[R[%rsp]];`<br>`R[%rsp]<-R[%rsp]+8`|将四字弹出栈|
%rsp代表栈指针

## 3.5 算术和逻辑操作

算术和逻辑操作分为四组：加载有效地址、一元操作、二元操作和移位

|种类|指令|效果|描述|
|-|-|-|-|
|加载有效地址|`leaq S,D`|`D <- &S`|加载有效地址|
|一元操作|`INC D`|D <- D+1|加1|
|一元操作|`DEC D`|D <- D-1|减1|
|一元操作|`NEG D`|D <- -D|取负|
|一元操作|`NOT D`|D <- ~D|取补|
|二元操作|`ADD S,D`|D <- D+S|加|
|二元操作|`SUB S,D`|D <- D-S|减|
|二元操作|`IMUL S,D`|D <- D*S|乘|
|二元操作|`XOR S,D`|D <- D^S|异或|
|二元操作|`OR S,D`|D <- D|S|或|
|二元操作|`AND S,D`|D <- D&S|与|
|移位|`SAL k,D`|D <- D<<k|左移|
|移位|`SHL k,D`|D <- D<<k|左移(等同于SAL)|
|移位|`SAR k,D`|D <- D>><sub>A</sub>k|算术右移|
|移位|`SHR k,D`|D <- D>><sub>L</sub>k|逻辑右移|
|||||
