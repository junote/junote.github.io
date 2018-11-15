---
layout: post
title:  "centos7 setup"
date:   2018-02-26
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
3. service network restart
4. yum install net-tools
~~~
2. tools
~~~
yum -y groupinstall "Development tools"
yum -y install glibc-devel.i686 texi2html texinfo chrpath samba samba-client

~~~
3. user
~~~
user add new
passwd new
visudo 

set new same as ROOT
~~~

4. selinux

~~~
#vi /etc/selinux/config
SELINUX=disabled

sestatus -v //查看selinux的状态
setenforce 0 //临时关闭selinux
~~~

5.firewall

~~~
//临时关闭防火墙
service iptables stop
service ip6tables stop
//永久关闭防火墙
chkconfig iptables off
chkconfig ip6tables off

~~~
## vbox
~~~
yum update
yum install gcc kernel-devel linux-headers-$(uname -r) dkms make bzip2 
reboot

cd media
mkdir cdrom
  //menu insert addin
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


## samba
1. setup
~~~
yum -y install samba samba-client
~~~
2. 配置Samba
~~~
#======================= Global Settings =====================================
[global]
        workgroup = MYGROUP
        server string = Samba Server Version %v
;       max protocol = SMB2
        security = share

#============================ Share Definitions ==============================
[ws]
        comment = Public Stuff
        path = /home/jcai/ws
        public = yes
        writable = yes
        guest ok = yes

        create mask = 0755
        directory mask = 0755
        available =yes
        browseable =yes
        forceuser =root
        forcegroup=root
~~~
3. restart
~~~
service nmb restart
service smb restart
~~~

## others

~~~
rpm -qa | sort  //check what setup
~~~