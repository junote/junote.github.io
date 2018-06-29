---
layout: post
title:  "centos7 setup"
date:   2017-02-26
categories: linux
tags: linux
mathjax: false
---
* content
{:toc}

## 启动配置
1. 网络
~~~
1. vi  /etc/sysconfig/network-scripts/ifcfg-enp2s0
2. set ONBOOT = yes
3. reboot
4. yum install net-tools
~~~
2. toos
~~~
yum install git
yum -y groupinstall "Development tools"



~~~
3. vim
~~~
yum install ncurses-devel
wget https://github.com/vim/vim/archive/master.zip
unzip master.zip
cd vim-master
cd src/
./configure --with-features=huge -enable-pythoninterp -enable-python3interp 
sudo make
sudo make insta

yum -y install epel-release
curl -o /etc/yum.repos.d/dperson-neovim-epel-7.repo https://copr.fedorainfracloud.org/coprs/dperson/neovim/repo/epel-7/dperson-neovim-epel-7.repo 
yum -y install neovim
~~~
4. python3
~~~
yum -y groupinstall "Development tools"
yum -y install zlib-devel bzip2-devel openssl-devel ncurses-devel sqlite-devel readline-devel tk-devel gdbm-devel db4-devel libpcap-devel xz-devel

wget https://www.python.org/ftp/python/3.6.4/Python-3.6.4.tar.xz

tar -xvJf  Python-3.6.4.tar.xz
cd Python-3.6.4
./configure
make && make install
~~~ 

## vbox
~~~
yum update
yum install gcc kernel-devel kernel-headers dkms make bzip2 
reboot

cd media
mkdir cdrom
mount /dev/sr0 /media/cdrom
cd /media/cdrom
./VBoxLinuxAdditions.run  --nox11
reboot


automount
在rc.local里添加没有成功。
在bashrc里添加,可以。

sudo mount -t vboxsf sharesrcdir lnxdesdir

~~~

## usb

~~~
under usb menu,select what you choose.

sudo mount -t ext4 /dev/sdb1 usb/

~~~
