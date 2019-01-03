---
layout: post
title:  "c++ thread"
date:   2018-05-09
categories: C++
tags: C++ 
mathjax: false
---
* content
{:toc}

## 启动线程
使用C++线程库启动线程，可以归结为构造std::thread对象.
~~~
void do_some_work();
std::thread my_thread(do_some_work);
~~~
## 等待线程结束
如果需要等待线程，相关的std::thread实例需要使用join()。
~~~
my_thread.join();
~~~
## 后台运行
使用detach()会让线程在后台运行，这就意味着主线程不能与之产生直接交互.
~~~
std::thread t(do_background_work);
t.detach();
assert(!t.joinable());
~~~
## 线程函数传递参数
#### 函数
~~~
void f(int i, std::string const& s);
std::thread t(f, 3, "hello");
~~~
#### 类函数
~~~
class X
{
public:
  void do_lengthy_work();
};
X my_x;
std::thread t(&X::do_lengthy_work,&my_x); 
~~~
#### 类
~~~
class X
{
public:
  void do_lengthy_work(int);
};
X my_x;
int num(0);
std::thread t(&X::do_lengthy_work, &my_x, num);
~~~

## 线程的所有权可移动，但不可拷贝
~~~
void some_function();
void some_other_function();
std::thread t1(some_function);            
std::thread t2=std::move(t1);            // t1的所有权就转移给了t2
t1=std::thread(some_other_function);    
std::thread t3;                            
t3=std::move(t2);                        // 将与t2关联线程的所有权转移到t3中
t1=std::move(t3);                        // 赋值操作将使程序崩溃
~~~



## 线程数
函数将返回能同时并发在一个程序中的线程数量。例如，多核系统中，返回值可以是CPU核芯的数量。返回值也仅仅是一个提示，当系统信息无法获取时，函数也会返回0。
~~~
std::thread::hardware_concurrency()
~~~
## 识别线程
线程标识类型是std::thread::id，可以通过两种方式进行检索。

第一种，可以通过调用std::thread对象的成员函数get_id()来直接获取。

第二种，当前线程中调用std::this_thread::get_id()(这个函数定义在<thread>头文件中)也可以获得线程标识。
## 等待

~~~
template< class Rep, class Period >
void sleep_for( const std::chrono::duration<Rep, Period>& sleep_duration )

template< class Clock, class Duration >
void sleep_until( const std::chrono::time_point<Clock,Duration>& sleep_time );
~~~
