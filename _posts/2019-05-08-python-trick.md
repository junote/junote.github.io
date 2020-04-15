---
layout: post
title:  "python 小花招"
date:   2019-05-08
categories: python
tags: python
mathjax: false
---
* content
{:toc}

## ipython

#### 简单流程
1. 在ipython里用命令模拟一下。
2. 在vscode里写出程序
3. 在ipython里用“%edit file”打开，把vscode程序拷进去
4. 用ipython调试。

#### ipython小花招
1. 自动保存运行

~~~
%load_ext autoreload
%autoreload 2
~~~
2. 执行

~~~
%bg: 使用独立线程在后台执行。
%rep: 获取上一次命令的输出，或提取某个历史命令。
%run: 用来执行一个脚本，并将相关对象导入交互环境上下文。使用起来类似于熟悉的python test.py 
~~~

3. 测试

~~~
%prun: 使用 profile 获取代码执行的性能统计。
%time: 获取代码执行时间。
%timeit: 通过多次循环，获得最佳的执行时间评测。 这个命令用来测试一条命令执行的时间，一般而且，会重复100次运行这个命令，然后取出最好的3个结果取平均值。
%timeit [x*x for x in range(100000)]
调试
%debug: 激活交互调试模式。
%pdb: 激活 pdb 调试模式，在引发异常时自动切入 pdb 调试命令行。
~~~



## python
#### python小花招
1. 重新加载
~~~
import sys, importlib
importlib.reload(sys.modules['foo'])
from foo import bar
~~~