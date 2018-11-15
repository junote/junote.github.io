---
layout: post
title:  "Linux command "
date:   2018-08-06
categories: linux
tags: linux
mathjax: false
---
* content
{:toc}

## version

1. kernel version

~~~
cat /proc/version

uname -ar
~~~

2. release

~~~
lsb_release -a
cat /etc/issue
cat /etc/redhat-release
~~~


## cut

cut命令用来显示行中的指定部分，删除文件中指定字段。

~~~
-b：仅显示行中指定直接范围的内容；
-c：仅显示行中指定范围的字符；
-d：指定字段的分隔符，默认的字段分隔符为“TAB”；
-f：显示指定字段的内容；
-n：与“-b”选项连用，不分割多字节字符；
--complement：补足被选择的字节、字符或字段；
--out-delimiter=<字段分隔符>：指定输出内容是的字段分割符；
--help：显示指令的帮助信息；
--version：显示指令的版本信息。
~~~


cut命令可以将一串字符作为列来显示，字符字段的记法：
~~~
    N-：从第N个字节、字符、字段到结尾；
    N-M：从第N个字节、字符、字段到第M个（包括M在内）字节、字符、字段；
    -M：从第1个字节、字符、字段到第M个（包括M在内）字节、字符、字段。
~~~

example
显示所有文件名
~~~
ls -alt|cut  -b48-
~~~

~~~
echo $PATH
/usr/kerberos/bin:/usr/local/bin:/bin:/usr/bin:/home/changquan.scq/bin

echo $PATH | cut -d: -f2-
/usr/local/bin:/bin:/usr/bin:/home/changquan.scq/bin
~~~

## sed
[sed](http://man.linuxde.net/sed)是一种流编辑器，它是文本处理中非常中的工具，能够完美的配合正则表达式使用.处理时，把当前处理的行存储在临时缓冲区中，称为“模式空间”（pattern space），接着用sed命令处理缓冲区中的内容，处理完成后，把缓冲区的内容送往屏幕。文件内容并没有 改变，除非你使用重定向存储输出。


几个简单sample

~~~
sed 's/book/books/' file  //替换操作：s命令

sed '/^$/d' file //删除空白行：

sed -n “3p” filename #输出文件的第3行
sed -n “2,5p“ filename #输出文件的第2到5行
sed ”/abc/d“ filename #删除包含“abc”的行
sed “2d” filename #删除第2行
sed ”$d“ filename #删除最后一行



~~~


## awk
[awk](http://man.linuxde.net/awk)是一种编程语言，用于在linux/unix下对文本和数据进行处理。数据可以来自标准输入(stdin)、一个或多个文件，或其它命令的输出。

语法形式

~~~
awk [options] 'script' var=value file(s)
awk [options] -f scriptfile var=value file(s)

awk 'BEGIN{ print "start" } pattern{ commands } END{ print "end" }' file
~~~

一个awk脚本通常由：BEGIN语句块、能够使用模式匹配的通用语句块、END语句块3部分组成，这三个部分是可选的。任意一个部分都可以不出现在脚本中，脚本通常是被单引号或双引号中.


options

~~~
$n 当前记录的第n个字段，比如n为1表示第一个字段，n为2表示第二个字段。 
$0 这个变量包含执行过程中当前行的文本内容。
FILENAME 当前输入文件的名。
FS 字段分隔符（默认是任何空格）。
NF 表示字段数，在执行过程中对应于当前的字段数。
NR 表示记录数，在执行过程中对应于当前的行号。
OFMT 数字的输出格式（默认值是%.6g）。
OFS 输出字段分隔符（默认值是一个空格）。
ORS 输出记录分隔符（默认值是一个换行符）。
RS 记录分隔符（默认是一个换行符）。
~~~


example

~~~
echo -e "line1 f2 f3\nline2 f4 f5\nline3 f6 f7" | awk '{print "Line No:"NR", No of fields:"NF, "$0="$0, "$1="$1, "$2="$2, "$3="$3}' 

Line No:1, No of fields:3 $0=line1 f2 f3 $1=line1 $2=f2 $3=f3
Line No:2, No of fields:3 $0=line2 f4 f5 $1=line2 $2=f4 $3=f5
Line No:3, No of fields:3 $0=line3 f6 f7 $1=line3 $2=f6 $3=f7
~~~

打印倒数第二个字段

~~~
echo -e "line1 f2 f3\n line2 f4 f5" | awk '{print $(NF-1)}'
~~~

打印文件名和容量
~~~
ls -alt |awk 'NR==2 {print $5 $9 }'
~~~
## grep


## 用户和用户组
1. 与用户（user）和用户组（group）相关的配置文件；
~~~
/etc/passwd 注：用户（user）的配置文件；
/etc/shadow 注：用户（user）影子口令文件；

/etc/group 注：用户组（group）配置文件；
/etc/gshadow 注：用户组（group）的影子文件；
~~~

2. 管理用户的相关工具或命令；

~~~
useradd    注：添加用户 
adduser    注：添加用户
passwd     注：为用户设置密码
usermod  注：修改用户命令，可以通过usermod 来修改登录名、用户的家目录等等；
pwcov       注：同步用户从/etc/passwd 到/etc/shadow 
pwck         注：pwck是校验用户配置文件/etc/passwd 和/etc/shadow 文件内容是否合法或完整；
pwunconv  注：是pwcov 的立逆向操作，是从/etc/shadow和 /etc/passwd 创建/etc/passwd ，然后会删除 /etc/shadow 文件；
finger        注：查看用户信息工具
id              注：查看用户的UID、GID及所归属的用户组
chfn          注：更改用户信息工具
su             注：用户切换工具
sudo         注：sudo 是通过另一个用户来执行命令（execute a command as another user），su 是用来切换用户，然后通过切换到的用户来完成相应的任务。
visudo      注：visodo 是编辑 /etc/sudoers 的命令；也可以不用这个命令，直接用vi 来编辑 /etc/sudoers 的效果是一样的；
sudoedit  注：和sudo 功能差不多；
~~~

3. 管理用户组的相关工具或命令；

~~~
groupadd  注：添加用户组；
groupdel         注：删除用户组；
groupmod        注：修改用户组信息
groups     注：显示用户所属的用户组
grpck
grpconv   注：通过/etc/group和/etc/gshadow 的文件内容来同步或创建/etc/gshadow ，如果/etc/gshadow 不存在则创建；
grpunconv   注：通过/etc/group 和/etc/gshadow 文件内容来同步或创建/etc/group ，然后删除gshadow文件；
~~~


## trap

trap命令用于指定在接收到信号后将要采取的动作，常见的用途是在脚本程序被中断时完成清理工作。

~~~
trap "exit 1" HUP INT PIPE QUIT TERM
~~~
表示当shell收到HUP INT PIPE QUIT TERM这几个命令时，当前执行的程序会读取参数“exit 1”，并将它作为命令执行。

|信号名称| 	信号数|	描述|
|-|-|-|
|SIGHUP|1|本信号在用户终端连接(正常或非正常)结束时发出, 通常是在终端的控制进程结束时, 通知同一session内的各个作业, 这时它们与控制终端不再关联。|
|SIGINT|2|程序终止(interrupt)信号, 在用户键入INTR字符(通常是Ctrl C)时发出。|
|SIGQUIT|	3|	和SIGINT类似, 但由QUIT字符(通常是Ctrl /)来控制. |
|SIGFPE	|8|	在发生致命的算术运算错误时发出. |
|SIGKILL|	9|	用来立即结束程序的运行.|
|SIGALRM|	14|	时钟定时信号, 计算的是实际的时间或时钟时间. alarm函数使用该信号。|
|SIGTERM|	15|	程序结束(terminate)信号, 与SIGKILL不同的是该信号可以被阻塞和处理. 通常用来要求程序自己正常退出. shell命令kill缺省产生这个信号。|


1. 清理临时文件
~~~
trap "rm $WORKDIR/work1$$ $WORKDIR/dataout$$; exit" 1 2
~~~

2. 忽略信号
~~~
trap '' 2
~~~

3. 重设陷阱

~~~
 trap 1 2
~~~

## 用shell来发tcp包

~~~
    exec 8<>/dev/tcp/10.100.70.139/19006
    echo -e "stats" >&8
~~~
tcpdump
~~~
udo tcpdump -iany port 19006 -Xnlps0
tcpdump: verbose output suppressed, use -v or -vv for full protocol decode
listening on any, link-type LINUX_SLL (Linux cooked), capture size 65535 bytes
23:56:54.177781 IP 10.100.70.139.34209 > 10.100.70.139.19006: Flags [S], seq 2048518213, win 43690, options [mss 65495,sackOK,TS val 1173337789 ecr 0,nop,wscale 8], length 0
        0x0000:  4500 003c 5ef8 4000 4006 39e6 0a64 468b  E..<^.@.@.9..dF.
        0x0010:  0a64 468b 85a1 4a3e 7a19 e845 0000 0000  .dF...J>z..E....
        0x0020:  a002 aaaa a20c 0000 0204 ffd7 0402 080a  ................
        0x0030:  45ef b6bd 0000 0000 0103 0308 0000 0000  E...............
        0x0040:  0000 0000 0000 0000 0000 0000            ............
23:56:54.177794 IP 10.100.70.139.19006 > 10.100.70.139.34209: Flags [S.], seq 480321333, ack 2048518214, win 43690, options [mss 65495,sackOK,TS val 1173337789 ecr 1173337789,nop,wscale 8], length 0
        0x0000:  4500 003c 0000 4000 4006 98de 0a64 468b  E..<..@.@....dF.
        0x0010:  0a64 468b 4a3e 85a1 1ca1 1f35 7a19 e846  .dF.J>.....5z..F
        0x0020:  a012 aaaa a20c 0000 0204 ffd7 0402 080a  ................
        0x0030:  45ef b6bd 45ef b6bd 0103 0308 0000 0000  E...E...........
        0x0040:  0000 0000 0000 0000 0000 0000            ............
~~~
## reference

1. [Bash 快速参考表](https://github.com/LeCoupa/awesome-cheatsheets/blob/master/languages/bash.sh)



