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
setenv CFLAGS "--sysroot=${SYSROOT}" 
setenv CPPFLAGS " --sysroot=${SYSROOT}" 
setenv LDFLAGS " -rdynamic -v --sysroot=${SYSROOT}" 
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


vi Modules/Setup.dist  //配置moudles

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
6. 安装setuptool 和pip， 下载如下包，解压后用命令安装。

~~~
python3 setup.py install --prefix=/mnt/sdcard/python3
~~~

6. 安装ipython，下载如下包，解压后用命令安装。
在串口下无法显示输入，在ssh下可以。

~~~
pip install backcall-0.1.0.zip
pip install simplegeneric-0.8.1.zip
pip install wcwidth-0.1.7-py2.py3-none-any.whl
pip install ptyprocess-0.6.0-py2.py3-none-any.whl
pip install decorator-4.4.0-py2.py3-none-any.whl
pip install ipython_genutils-0.2.0-py2.py3-none-any.whl
pip install six-1.12.0-py2.py3-none-any.whl
pip install traitlets-4.3.2-py2.py3-none-any.whl
pip install pexpect-4.7.0-py2.py3-none-any.whl
pip install pickleshare-0.7.5-py2.py3-none-any.whl
pip install Pygments-2.3.1-py2.py3-none-any.whl
pip install setuptools_scm-3.3.0-py2.py3-none-any.whl
pip install prompt_toolkit-2.0.9-py3-none-any.whl
pip install parso-0.4.0-py2.py3-none-any.whl
pip install jedi-0.13.3-py2.py3-none-any.whl
pip install ipython-7.5.0-py3-none-any.whl
~~~



7. 移除本地的python36环境 

~~~
rm -rf /usr/local/lib/python3.6
rm -rf /usr/local/bin/2to3-3.6 
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

3. 修改配置文件 CFLAGS 和 LDFLAGS

~~~
5 CFLAGS=$(OPT) -Wall -W -Wno-parentheses -Wstrict-prototypes -Wmissing-prototypes --sysroot=${SYSROOT}
6 LDFLAGS     =     -rdynamic -v --sysroot=${SYSROOT}
~~~

4. 编译

~~~
make HOST=linux CROSS_COMPILE=$CROSS_COMPILE ZLIB=no  DNS=no 
~~~

5. 把生成的lspci和setpci拷贝到sd卡并且export。


#### reference
1. [交叉编译Python3.6](https://blog.csdn.net/whahu1989/article/details/86482669)
2. [交叉编译Python-3.4.2 ](http://ljgabc.github.io/2015/04/24/2015-04-24-%E4%BA%A4%E5%8F%89%E7%BC%96%E8%AF%91Python-3-4-2/)