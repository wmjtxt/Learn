STL源码剖析
====

## 1.2 STL六大组件

#### 1.容器(containers)
vector, list, deque, set, map, 用于存放数据. class template
#### 2.算法(algorithms)
sort, search, copy, erase. function template
#### 3.迭代器(iterators)
泛型指针. 共五种类型, 重载了operator\*, operator->, operator++, operator-- 所有STL容器都附带有自己的迭代器. 原生指针也是一种迭代器
#### 4.仿函数(functors)
行为类似函数, 重载了operator()的class template. 函数指针可视为狭义的仿函数
#### 5.配接器或适配器(adapters)
queue和stack是一种容器配接器, 底部实现是deque
#### 6.配置器(allocators)
负责空间配置与管理. class template


