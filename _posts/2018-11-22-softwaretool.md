---
layout: post
title:  "software tool"
date:   2018-11-22
categories: tool
tags: win linux
mathjax: false
---
* content
{:toc}


## commandline
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


## WinSoft

#### File

|tool|download addr|
|:-:|:-:|
|total commander|https://www.ghisler.com/|
|everything|http://www.voidtools.com/|
|listary|https://www.listary.com/download|

#### Develep
|tool||
|-|-|
|vscode|https://code.visualstudio.com/|
| Beyond Compare |http://www.scootersoftware.com/download.php|
|hxd|https://mh-nexus.de/en/hxd/|
|notepad++|https://notepad-plus-plus.org/|

## SSH
|tool||
|-|-|
|xshell|http://www.netsarang.com/products/xsh_overview.html|
|mobaxterm|https://mobaxterm.mobatek.net/download.html|
|putty|for linux serial port|
|SecureCRT|for win script|




## linux

#### fzf
fzf是目前最快的fuzzy finder。使用golang编写。结合其他工具(比如ag和fasd)可以完成非常多的工作。
让你通过输入模糊的关键词就可以定位文件或文件夹。当你的思维也习惯了模糊匹配后，在工作中可以大幅提高你的工作效率。
模糊搜索的概念如下，你记得文件名含有con， te, go, 那么你只需要把所有文件送给fzf, 然后在窗口里输入con te go就可以了，不管实现名是test_continus_go还是go_cont_test都会匹配上。


1. 安装
~~~
git clone --depth 1 https://github.com/junegunn/fzf.git ~/.fzf
~/.fzf/install
//upgrade
cd ~/.fzf && git pull && ./install
~~~
2. 快捷键

 |快捷键|作用|
 |-|-|
 |CTRL-T|在命令行下按下ctrl-t会打开fzf窗口，如果你选中某个条目并按下Enter， 选中的条目会被拷贝到命令行上|
 |CTRL-R|在命令行下按下ctrl-r, fzf会列出history命令，选中条目并离开fzf的话， 选中条目会被拷到命令行上|
 |ALT-C|在命令行上按下alt-c, 会列出当前文件夹下的目录，选中条目会自动进入到相应目录|
 |Ctrl-J/Ctrl-K|可以用来将光标上下移动|
3. 语法
fzf默认会以“extened-search"模式启动， 这种模式下你可以输入多个以空格分隔的搜索关键词， 如^music .mp3$, sbtrkt !fire.

|Token |	Match type| 	Description|
|-|-|-|
|sbtrkt |	fuzzy-match |	匹配sbtrkt|
|^music |	prefix-exact-match 	|以music开头|
|.mp3^ |	suffix-exact-match |	以.mp3结尾|
|'wild |	exact-match(quoted) |	精确包含wild|
|!fire |	inverse-exact-match |	不包含fire|
|!.mp3$ |	inverse-suffix-exact-match| 	不以.mp3结尾|
#### ncdu

Ncdu (NCurses Disk Usage) 是一个基于Ncurses库的du命令的界面。它通过大家熟知的du命令,为用户提供一个快速且容易被使用的界面。它可以显示磁盘使用的百分比,且允许你使用ncurses库的方式在目录之间导航。


#### ag

Ag 是类似ack， grep的工具, 它来在文件中搜索相应关键字。

~~~
yum install the_silver_searcher
~~~
#### tig
tig是git的一个插件，相对于git log来说显示日志记录比较漂亮、直观和方便tig。

#### tmux

### htop

#### guake

#### sougoupinying
[setup](https://blog.csdn.net/lupengCSDN/article/details/80279177)

#### autojump

#### Remmina

远程win7

#### PyCharm
python

#### IDEA 
java

#### meld

对比

Putty 

Master PDF Editor 

foxsit

nylas-mail
