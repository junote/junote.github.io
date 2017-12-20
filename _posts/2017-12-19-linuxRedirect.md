---
layout: post
title:  "linux重定向"
date:   2017-12-19
categories: linux 
tags: shell
mathjax: false
---
* content
{:toc}

linux启动后，会默认打开3个文件描述符，分别是：标准输入standard input 0,正确输出standard output 1,错误输出：error output 2。

一个命令执行了：

先有一个输入：输入可以从键盘，也可以从文件得到

命令执行完成：成功了，会把成功结果输出到屏幕：standard output默认是屏幕

命令执行有错误：会把错误也输出到屏幕上面：standard error默认也是指的屏幕

这些默认的输出，输入都是linux系统内定的，我们在使用过程中，有时候并不希望执行结果输出到屏幕。我想输出到文件或其它设备。这个时候我们就需要进行输出重定向了。 

#### 输出重定向

格式：command-line1 [1-n] > file或文件操作符或设备

上面命令意思是：将一条命令执行结果（标准输出，或者错误输出，本来都要打印到屏幕上面的）  重定向其它输出设备（文件，打开文件操作符，或打印机等等）1,2分别是标准输出，错误输出。

~~~
#正确输出与错误输出都显示在屏幕了，现在需要把正确输出写入suc.txt
# 1>可以省略，不写，默认所至标准输出

ls test.sh test1.sh 1>suc.txt
ls: test1.sh: 没有这个文件和目录

cat suc.txt 
test.sh

#把错误输出，不输出到屏幕，输出到err.txt
ls test.sh test1.sh 1>suc.txt 2>err.txt
cat suc.txt err.txt 
test.sh
ls: test1.sh: 没有这个文件和目录

#继续追加把输出写入suc.txt err.txt  “>>”追加操作符
ls test.sh test1.sh 1>>suc.txt 2>>err.txt 

#将错误输出信息关闭掉
ls test.sh test1.sh 2>&-
test.sh

ls test.sh test1.sh 2>/dev/null
test.sh
#&[n] 代表是已经存在的文件描述符，&1 代表输出 &2代表错误输出 &-代表关闭与它绑定的描述符
#/dev/null 这个设备，是linux 中黑洞设备，什么信息只要输出给这个设备，都会给吃掉 

#关闭所有输出
ls test.sh test1.sh  1>&- 2>&- 

#关闭 1 ，2 文件描述符
ls test.sh test1.sh  2>/dev/null 1>/dev/null

#将1,2 输出转发给/dev/null设备 
ls test.sh test1.sh >/dev/null 2>&1

#将错误输出2 绑定给 正确输出 1，然后将 正确输出 发送给 /dev/null设备  这种常用
ls test.sh test1.sh &>/dev/null
#& 代表标准输出 ，错误输出 将所有标准输出与错误输出 输入到/dev/null文件
~~~

注意：

1. shell遇到”>”操作符，会判断右边文件是否存在，如果存在就先删除，并且创建新文件。不存在直接创建。 无论左边命令执行是否成功。右边文件都会变为空。

2. “>>”操作符，判断右边文件，如果不存在，先创建。以添加方式打开文件，会分配一个文件描述符[不特别指定，默认为1,2]然后，与左边的标准输出（1）或错误输出（2） 绑定。

3. 当命令执行完，绑定文件的描述符也自动失效。0,1,2又会空闲。

4. 一条命令启动，命令的输入，正确输出，错误输出，默认分别绑定0,1,2文件描述符。

5. 一条命令在执行前，先会检查输出是否正确，如果输出设备错误，将不会进行命令执行

#### 输入重定向

格式：command-line [n] <file或文件描述符&设备

命令默认从键盘获得的输入，改成从文件，或者其它打开文件以及设备输入。执行这个命令，将标准输入0，与文件或设备绑定。将由它进行输入。

~~~
cat > catfile 
testing 
cat file test
#这里按下 [ctrl]+d 离开 
#从标准输入【键盘】获得数据，然后输出给catfile文件
 
cat>catfile <test.sh
#cat 从test.sh 获得输入数据，然后输出给文件catfile
 
 
 cat>catfile <<eof
test a file
test!
eof 
#<< 这个连续两个小符号， 他代表的是『结束的输入字符』的意思。这样当空行输入eof字，输入自动结束，不用ctrl+D
~~~

#### exec绑定重定向
格式：exec 文件描述符[n] <或> file或文件描述符或设备

在上面讲的输入，输出重定向 将输入，输出绑定文件或设备后。只对当前那条指令是有效的。如果需要在绑定之后，接下来的所有命令都支持的话。就需要用exec命令

~~~
exec 6>&1
#将标准输出与fd 6绑定
 
ls  /proc/self/fd/ 
0  1  2  3  6
#出现文件描述符6

exec 1>suc.txt
#将接下来所有命令标准输出，绑定到suc.txt文件（输出到该文件）
 
 ls -al
#执行命令，发现什么都不返回了，因为标准输出已经输出到suc.txt文件了

exec 1>&6
#恢复标准输出
 
 
exec 6>&-
#关闭fd 6描述符
 
ls /proc/self/fd/
0  1  2  3
~~~

#### 总结

||| 
|-|:-:| 
|>|输出重定向到一个文件或设备 覆盖原来的文件|
|>!|输出重定向到一个文件或设备 强制覆盖原来的文件|
|>>| 输出重定向到一个文件或设备 追加原来的文件|
|<| 输入重定向到一个程序|
|>& |将一个标准错误输出重定向到一个文件或设备 覆盖原来的文件|
|>&-|关闭与它绑定的描述符|
|2>&1|将一个标准错误输出重定向到标准输出|
|command < filename >filename2|把command命令以filename文件作为标准输入，以filename2文件作为标准输出|
|||