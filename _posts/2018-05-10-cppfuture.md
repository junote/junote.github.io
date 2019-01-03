---
layout: post
title:  "c++ thread future"
date:   2018-05-10
categories: C++
tags: C++ thread
mathjax: false
---
* content
{:toc}


std::condition_variable可以用于异步事件的重复通知，但是有些时候可能只等待事件发生一次，比如：等待特定的航班，用条件变量大杀器有点浪费了。C++11标准库提供了几种异步任务机制。通常thread不能返回线程执行的结果(可以通过引用参数返回)，而在异步处理当中很多时候都需要获得计算的结果。如果只获取结果一次那么选用future，即通过future获取了结果后，后续再通过此future获取结果将会出错。

future 头文件中包含了以下几个类和函数：

- Providers 类：std::promise, std::package_task
- Futures 类：std::future, shared_future.
- Providers 函数：std::async()
- 其他类型：std::future_error, std::future_errc, std::future_status, std::launch.

std::future提供了一个访问异步操作结果的机制，它和线程是一个级别的属于低层次的对象，在它之上高一层的是std::packaged_task和std::promise，他们内部都有future以便访问异步操作结果，std::packaged_task包装的是一个异步操作，而std::promise包装的是一个值，都是为了方便异步操作的，因为有时我需要获取线程中的某个值，这时就用std::promise，而有时我需要获一个异步操作的返回值，这时就用std::packaged_task。


## future_status

|状态|作用| 
|-|:-:| 
|future_status::deferred|The function to calculate the result has not been started yet |
|future_status::ready|The result is ready |
|future_status::timeout|The timeout has expired|


~~~
#include <iostream>
#include <future>
#include <thread>
#include <chrono>
 
int main()
{
    std::future<int> future = std::async(std::launch::async, [](){ 
        std::this_thread::sleep_for(std::chrono::seconds(3));
        return 8;  
    }); 
 
    std::cout << "waiting...\n";
    std::future_status status;
    do {
        status = future.wait_for(std::chrono::seconds(1));
        if (status == std::future_status::deferred) {
            std::cout << "deferred\n";
        } else if (status == std::future_status::timeout) {
            std::cout << "timeout\n";
        } else if (status == std::future_status::ready) {
            std::cout << "ready!\n";
        }
    } while (status != std::future_status::ready); 
 
    std::cout << "result is " << future.get() << '\n';
}
~~~
possible result：
~~~
waiting...
timeout
timeout
ready!
result is 8
~~~

## promise

promise为获取线程函数中的某个值提供便利，在线程函数中给外面传进来的promise赋值，当线程函数执行完成之后就可以通过promis获取该值了，值得注意的是取值是间接的通过promise内部提供的future来获取的。它的基本用法：

~~~
std::promise<int> pr;
std::thread t([](std::promise<int>& p){ p.set_value_at_thread_exit(9); },std::re(pr));
std::future<int> f = pr.get_future();
auto r = f.get();
~~~

## packaged_task

packaged_task它包装了一个可调用的目标（如function, lambda expression, bind expression, or another function object）,以便异步调用。

~~~
std::packaged_task<int()> task([](){ return 7; });
std::thread t1(std::ref(task)); 
std::future<int> f1 = task.get_future(); 
auto r1 = f1.get();
~~~



参考：

1. [用C++11的std::async代替线程的创建](https://blog.csdn.net/yockie/article/details/50595958)
2. [C++并发实战13：std::future、std::async、std::promise、std::packaged_task](https://blog.csdn.net/liuxuejiang158blog/article/details/17354115)
3. [使用期望等待一次性事件](http://wiki.jikexueyuan.com/project/cplusplus-concurrency-action/content/chapter4/4.2-chinese.html)
