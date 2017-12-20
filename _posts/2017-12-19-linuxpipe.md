---
layout: post
title:  "linux管道"
date:   2017-12-19
categories: linux 
tags: shell
mathjax: false
---
* content
{:toc}

bash 命令执行的时候有输出的数据会出现，那么如果这群数据必需要经过几道手续之后才能得到我们所想要的格式，应该如何来设定？这就牵涉到管线命令的问题了（ pipe ），管线命令使用的是『 | 』。

例子：简单的管线命令
假设我们要读取 last 这个指令中，那个 root 登入的『次数』应该怎么作？
那么我所进行的步骤是：
1. 执行 last ，将所有这个月的所有人登入数据取出来；
2. 使用 grep 将上面的输出数据（stdout）当中的 root 撷取出来，其它的不要；
3. 使用 wc 这个可以计算行数的指令将上一步的数据计算行数！

由于 last 的输出是一行代表一次登入，所以只要计算几行就代表登入几次的意思，经由上面三个步骤，将 last 数据逐步的筛选，就可以得到我们的数据了！整个命令可以写成如下：

    last | grep root | wc -l

这个管线命令『 | 』仅能处理经由前面一个指令传来的正确信息，也就是standard 
output ( STDOUT ) 的信息，对于 stdandard error 并没有直接处理的能力。


#### cut

~~~
语法：cut -d "分隔字符" [-cf] fields

参数说明：
-d ：后面接的是用来分隔的字符，预设是『空格符』
-c ：后面接的是『第几个字符』
-f ：后面接的是第几个区块？

cat /etc/passwd | cut -d ":" -f 1
#将 passwd 这个文件里面，每一行里头的 : 用来作为分隔号，而列出第一个区块！也就是姓名所在啦！

last | cut -c1-20
#将 last 之后的数据，每一行的 1-20 个字符取出来！
~~~

####sort

~~~
语法： sort [-t 分隔符] [-k 列选择] [-nru]

参数说明：
-t 分隔符：使用分隔符来隔开不同区间，预设是 tab
+start -end：由第 start 区间排序到 end 区间
-n ：使用『纯数字』排序（否则就会以文字型态来排序）
-r ：反向排序
-u ：相同出现的一行，只列出一次！

cat /etc/passwd | sort
将列出来的个人账号排序！

cat /etc/passwd | sort -t: -k 1 -n
将个人账号中，以使用者 ID 来排序

cat /etc/passwd | sort -t: -k 1 -nr
反相排序
~~~

#### wc

~~~
语法： wc [-lmw]
参数说明：
-l ：多少行
-m ：多少字符
-w ：多少字

范例： cat /etc/passwd | wc -l
这个文件里头有多少行？
cat /etc/passwd | wc -w
这个文件里头有多少字！？
~~~
