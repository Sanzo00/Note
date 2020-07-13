# STL源码剖析

STL六大组件
- 容器 (containers)

  各种数据结构，如vector、list、deque、set、map等，用来存放数据

- 算法（algorithms）

  各种常用算法，如sort，search，copy，erase等。

- 迭代器（iterators）

  扮演容器和算法之间的胶合剂，是所谓的"泛型编程"。

- 仿函数（functors）

  行为类似函数，可作为算法的某种策略（policy），从实现角度看，仿函数是一种重载了operator()的class或class template。一般函数指针可以看作是狭义的仿函数。

- 配接器（adapters）

  用来修饰容器（containers）或仿函数（functors）或迭代器（iterators）接口的东西，例如STL提供的queue和stack，看似为容器，其实是一种容器配接器，底层借助deque实现。改变functor接口者，称为function adapter；改变container接口者，称为iterator adapter。

- 配置器（allocators）

  负责空间配置与管理，实现了动态空间配置、空间管理、空间释放的class template。

STL六大组件的交互关系：Container通过Allocator取得数据存储空间，Algorithm通过iterator存取Container内容，Functor可以协助Alogorithm完成不同的策略变化，Adapter可以修饰或套接Functor。

![](img/stl_six_mode.png)
