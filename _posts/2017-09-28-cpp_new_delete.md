---
layout: post
title:  "C++使用new动态分配存储空间"
date:   2017-09-28
categories: C++ 
tags: C++
mathjax: true
---


```
 1 // 使用new动态分配存储空间
 2 
 3 #include<iostream>
 4 using std::cout;
 5 
 6 int main()
 7 {
 8     // 第1种方式
 9     int *a=new int;
10     *a=1;
11     cout<<"使用第一种方式进行动态分配存储空间的结果为:\n"
12         <<"*a= "<<*a<<std::endl;
13     delete a;  // 释放动态存储空间
14     // 第2种方式
15     int *b=new int(2);
16     cout<<"使用第一种方式进行动态分配存储空间的结果为:\n"
17         <<"*b= "<<*b<<std::endl;
18     delete b;  // 释放动态存储空间
19     // 第3种方式
20     int *c;
21     c=new int(3);
22     cout<<"使用第一种方式进行动态分配存储空间的结果为:\n"
23         <<"*c= "<<*c<<std::endl;
24     delete c; // 释放动态存储空间
25 
26     // 动态创建数组
27     float *d=new float [3];
28     d[0]=3;
29     d[1]=6;
30     d[2]=8;
31     cout<<"d[0]= "<<d[0]<<std::endl;
32     d=d+1;       //数组名和指针之间的根本区别
33     cout<<"d[0]= "<<d[0]<<std::endl;
34     d=d-1;
35     cout<<"d[0]= "<<d[0]<<std::endl;
36     delete [] d; // 释放动态存储空间
37     return 0;
38 }

复制代码
```
