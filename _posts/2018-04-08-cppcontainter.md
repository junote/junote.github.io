---
layout: post
title:  "c++ STL 容器"
date:   2018-04-08
categories: C++
tags: C++ STL
mathjax: false
---
* content
{:toc}

## vector 向量

相当于一个数组

在内存中分配一块连续的内存空间进行存储。支持不指定vector大小的存储。STL内部实现时，首先分配一个非常大的内存空间预备进行存储，即capacituy（）函数返回的大小，当超过此分配的空间时再整体重新放分配一块内存存储，这给人以vector可以不指定vector即一个连续内存的大小的感觉。通常此默认的内存分配能完成大部分情况下的存储。

优点：

1.  不指定一块内存大小的数组的连续存储，即可以像数组一样操作，但可以对此数组进行动态操作。通常体现在push_back() pop_back()
2. 随机访问方便，即支持'[]' 操作符和vector.at()
3.  节省空间。

缺点：
1. 在内部进行插入删除操作效率低。
2. 只能在vector的最后进行push和pop，不能在vector的头进行push和pop。
3.  当动态添加的数据超过vector默认分配的大小时要进行整体的重新分配、拷贝与释放.

参考 [cppref](http://www.cplusplus.com/reference/vector/vector/)

## list 双向链表

每一个结点都包括一个信息快Info、一个前驱指针Pre、一个后驱指针Post。可以不分配必须的内存大小方便的进行添加和删除操作。使用的是非连续的内存空间进行存储。

**优点**

1. 不使用连续内存完成动态操作。
2. 在内部方便的进行插入和删除操作
3. 可在两端进行push、pop

**缺点** 
1. 不能进行内部的随机访问，即不支持[ ]操作符和vector.at().
2. 相对于verctor占用内存多

参考 [cppref](http://www.cplusplus.com/reference/list/list/)

## deque 双端队列 double-end queue
deque是在功能上合并了vector和list。

优点

1. 随机访问方便，即支持[ ]操作符和vector.at()
2. 在内部方便的进行插入和删除操作
3. 可在两端进行push、pop

缺点

1. 占用内存多

参考 [cppref](http://www.cplusplus.com/reference/deque/deque/)
## forward-list 单向链表（C++11）

相对于list删除了一个方向，相应减少内存。

优点：
1. 在容器内的任何位置中的元素的插入、提取和移动操作效率更高。
缺点：
1. 缺乏直接访问他们的位置的元素

参考 [cppref](http://www.cplusplus.com/reference/forward_list/forward_list/)


## array 数组（C++11）

跟数组并没有太大区别

Arrays是固定大小的顺序容器:他们拥有一定数目的元素并整理成一个严格的线性序列。

Array类仅仅只是增加了一层全局函数，以使它可以像标准容器一样使用。

零大小的Arrays是有效的，但是不可以被成员函数front、back、data间接引用。

参考 [cppref array](http://www.cplusplus.com/reference/array/array/)


## stack

实现数据的栈操作，后进先出，LIFO, last in first out。

参考 [cppref](http://www.cplusplus.com/reference/array/array/)

## queue

实现数据的队列操作，FIFO，first in first out，先进先出。

参考 [cppref](http://www.cplusplus.com/reference/queue/queue/)


## map,mutimap,unordered_map,unordered_mutimap

map映照容器的元素数据是一个键值和一个映照数据组成的，键值与映照数据之间具有一一映照的关系。

map映照容器的数据结构是采用红黑树来实现的，插入键值的元素不允许重复，比较函数只对元素的键值进行比较，元素的各项数据可通过键值检索出来。

mutimap 允许键值重复。
unordered_map 不排序，键单一。
unordered_mutimap 不排序,允许键值重复

参考 [cppref](http://www.cplusplus.com/reference/map/map/)

## set,mutiset,unordered_set,unordered_mutiset
set是集合  
包含了经过排序了的数据，这些数据的值(value)必须是唯一的。
Set和Map的区别在于Set只含有Key，而Map有一个Key和Key所对应的Value两个元素。

mutiset 允许键值重复。
unordered_set 不排序，键单一。
unordered_mutiset 不排序,允许键值重复

参考 [cppref](http://www.cplusplus.com/reference/set/set/)

## 使用区别
1. 如果你需要高效的随即存取，而不在乎插入和删除的效率，使用vector 
2. 如果你需要大量的插入和删除，而不关心随即存取，则应使用list 
3. 如果你需要随即存取，而且关心两端数据的插入和删除，则应使用deque
4. 如果是用来快速查找固定数据，用map。
5. 如果是用来快速查找pair数据，用map。


注意：set（集合） 与map（映射） 的区别

*  二者均使用红黑树实现；
*  key需要支持<操作（能够比较，对于整个结构体而言，则无法比较）；
*  map侧重于key-value的快速查找；
*  set侧重于查看元素是否存在。

共同点：map和set中的元素无法排序。由于其具有二叉排序性质，故不能排序。