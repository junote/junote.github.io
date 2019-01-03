---
layout: post
title:  "交换机"
date:   2017-08-16
categories: 图解网络硬件 
tags: 以太网
mathjax: true
---
* content
{:toc}

####  以太数据帧种类
![](https://github.com/junote/junote.github.io/blob/master/img/switch01.png?raw=true)
####  数据帧的传输方式
* 直通转发  读取前导和目的地mac地址后转发。只能用在相同速率下，不能丢弃错误帧。不再使用。
* 碎片隔离（fragment-free） 读取前面64个字节，即一个时隙。没有发现冲突就继续转发。不再使用。
* 存储转发 读取所有帧内容后转发。
####  PHY模块
1. PHY处理数据的流程  
![](https://github.com/junote/junote.github.io/blob/master/img/switch02.png?raw=true)
2. PHY的三层  
![](https://github.com/junote/junote.github.io/blob/master/img/switch03.png?raw=true)

