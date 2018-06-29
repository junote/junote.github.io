---
layout: post
title:  "c++ chrono"
date:   2018-05-07
categories: C++
tags: C++ 
mathjax: false
---
* content
{:toc}

chrono是c++ 11中的时间库，提供计时，时钟等功能。

学习chrono，关键是理解里面时间段(Durations)、时间点(Time points)的概念。

## 精度
时钟节拍(时间精度)：

~~~
template <intmax_t N, intmax_t D = 1> class ratio;
~~~

其中N表示分子，D表示分母，默认用秒表示的时间单位。

~~~
std::chrono::microseconds = std::chrono::duration<int, std::ratio<1, 1000>>
std::chrono::minutes = std::chrono::duration<int, std::ratio<60>>
~~~

## 时间段
~~~
template <class Rep, class Period = ratio<1> >
class duration;
~~~
Rep表示一种数值类型，用来表示Period的数量，比如int float double。

Period是ratio类型，用来表示上面所说的单位精度，比如second milisecond。

1.  chrono中宏定义了许多特例化了的duration，就是常见的hours，miniutes，seconds，milliseconds等，使用std::chrono::milliseconds直接使用。
2. 成员函数count()返回单位时间的数量。
~~~
    std::chrono::milliseconds mscond(1000); // 1 second  
    std::cout << mscond.count() << " milliseconds.\n"; 
    // 1000  milliseconds.
~~~
3. 当不要求截断值的情况下(时转换成秒是没问题，但是秒转换成时就不行)时间段的转换是隐式
的。显示转换可以由 std::chrono::duration_cast<> 来完成。

## 时间点
~~~
template <class Clock, class Duration = typename Clock::duration>
  class time_point;
~~~
第一个模板参数Clock用来指定所要使用的时钟（标准库中有三种时钟，system_clock，steady_clock和high_resolution_clock。见时钟详解），第二个模板函数参数用来表示时间的计量单位(特化的std::chrono::duration<> )

时间点都有一个时间戳，即时间原点。chrono库中采用的是Unix的时间戳1970年1月1日 00:00。所以time_point也就是距离时间戳(epoch)的时间长度（duration）。

时间点有个重要的函数：duration time_since_epoch()  (用于获取当前时间点距离时间戳的时间长度)即经常用来得到当前时间点到1970年1月1日00:00的时间距离、该函数返回的duration的精度和构造time_point的时钟(Clock)有关.

## 时钟
chrono中有三种时钟：system_clock，steady_clock和high_resolution_clock。每一个clock类中都有确定的time_point, duration, Rep, Period类型。
1. system_clock：从系统获取的时钟；
2. steady_clock：不能被修改的时钟；
3. high_resolution_clock：高精度时钟，实际上是system_clock或者steady_clock的别名

三者都支持如下函数：
1. 成员函数now() 用于获取系统的当前时间
2. 由于各种time_point表示方式不同，chrono也提供了相应的转换函数 time_point_cast。
3. 其他成员函数：
~~~
    to_time_t() time_point转换成time_t秒

    from_time_t() 从time_t转换成time_point
~~~