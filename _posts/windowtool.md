---
layout: post
title:  "windows工具"
date:   2017-12-26
categories: windows 
tags: tools
mathjax: false
---
* content
{:toc}


#### 使用命令搜索(find)一个文件


1. 这个命令可能不是最优的
~~~
    dir  /s %directory% | findstr "%patern_text%"
    dir /s *.tcl |findstr "connect*"
~~~
 2. 或者自己安装一个Unix Utils的工具包，删除system32下的find，然后可以使用unix命令
 ~~~
    find . -name *.java | xargs grep xxx
~~~


#### tool list

|tool|download addr|
|:-:|:-:|
|tcmd||
|everything||
