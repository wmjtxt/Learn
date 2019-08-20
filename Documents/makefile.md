MAKEFILE
====

* 1.编译: 源文件(.c,.cpp,.cc) -> 中间代码文件(.o,.obj)
    * 编译阶段，编译器只检测语法。
* 2.链接: 中间代码文件(.o,.obj) (当文件太多时 -打包-> .lib文件(win),.a(unix)) ->执行文件

# 一、Makefile的规则

target... : prerequisites ...
    command
    ...
    ...

* 变量
* clean
