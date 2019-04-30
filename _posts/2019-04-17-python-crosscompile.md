---
layout: post
title:  "python3.6 powerpc crosscompile"
date:   2019-04-17
categories: tool
tags: tool
mathjax: false
---
* content
{:toc}

今年尝试在嵌入式环境写python，首先要做的就是把python移植到p2041上。


#### python
1. 从[python org](https://www.python.org/downloads/source/)下载python3.6的稳定版，譬如3.6.8. python3.3以后的编译和以前不一样，需要安装相同python到本机。
2. 解压，安装到本地服务器。

~~~
./configure
make
sudo make install
~~~

3. 配置嵌入式环境，对于p2040，menv设置工作目录，denv设置编译器。可以测试一下下面的CC，CXX能否工作。

~~~
source menv.sh
csh
source denv.sh
setenv CC ppce500mc-wrswrap-linux-gnu-gcc
setenv CXX  ppce500mc-wrswrap-linux-gnu-g++
setenv LD  ppce500mc-wrswrap-linux-gnu-ld
setenv AR  ppce500mc-wrswrap-linux-gnu-ar
setenv STRIP  ppce500mc-wrswrap-linux-gnu-strip
setenv RANLIB  ppce500mc-wrswrap-linux-gnu-ranlib
~~~

4. 编译安装

~~~
./configure --host=powerpc-wrs-linux-gnu 
--build=powerpc 
--disable-ipv6 
ac_cv_file__dev_ptmx=no 
ac_cv_file__dev_ptc=no 
--prefix=/home/jcai/ws/osm/python/install
//prefix 定义安装地址

make

make install
~~~
5. 测试， 把prefix下的文件打包放到SD卡，接着解压配置python环境。

~~~
unzip install.zip
mount /dev/mmcblk0p1  /mnt/sdcard/
export LANG=en_US.UTF-8
export PATH="/mnt/sdcard/python3/bin:$PATH"
export PYTHONBASE="/mnt/sdcard/python3"

python3

~~~
6. 安装ipython，下载如下包，解压后用命令安装。
在串口下无法显示输入，在ssh下可以
~~~
wcwidth，prompt_toolkit， backcall，ptyprocess，Pygments，traitlets setuptools simplegeneric setuptools_scm pickleshare pexpect decorator ipython_genutils six ipython

python3 setup.py install --prefix=/mnt/sdcard/python3
~~~

7. 移除本地的python36环境 

~~~
rm -rf /usr/local/lib/python3.6
rm -rf /usr/local/bin/2to3-3.6 to
rm -rf /usr/local/bin/pyvenv-3.6
rm -rf /usr/local/bin/pydoc3.6
rm -rf /usr/local/bin/idle3.6
rm -rf /usr/local/lib/libpython3.6m.a
rm -rf /usr/local/bin/python3.6*
rm -rf /usr/local/bin/python3.6m*
~~~

#### pciutils

1. 从[github](https://github.com/pciutils/pciutils)下载zip包，解压到服务器。
2. 如上，配置编译环境。

~~~
source menv.sh
csh
source denv.sh
~~~

3. 编译

~~~
make HOST=linux CROSS_COMPILE=$CROSS_COMPILE ZLIB=no  DNS=no 
~~~

4. 把生成的lspci和setpci拷贝到sd卡并且export。


#### reference
1. [交叉编译Python3.6](https://blog.csdn.net/whahu1989/article/details/86482669)
2. [交叉编译Python-3.4.2 ](http://ljgabc.github.io/2015/04/24/2015-04-24-%E4%BA%A4%E5%8F%89%E7%BC%96%E8%AF%91Python-3-4-2/)