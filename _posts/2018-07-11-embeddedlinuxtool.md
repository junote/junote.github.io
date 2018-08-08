---
layout: post
title:  "embedded linux tool"
date:   2018-07-11
categories: HW
tags: embedded linux 
mathjax: false
---
* content
{:toc}

## TFTP

#### ubuntu
1. tftp-hpa是客户端, tftpd-hpa是服务器端.
~~~
sudo apt-get install tftpd-hpa
sudo apt-get install tftp-hpa
~~~
2. 配置TFTP服务器 /etc/default/tftpd-hpa
~~~
TFTP_DIRECTORY="your tftpboot addr"
~~~
3. 重新启动TFTP服务
~~~
sudo service tftpd-hpa restart
sudo service tftpd-hpa status
~~~

#### uboot
1. 配置uboot ip，server ip，ethact

~~~
setenv ethact FM1@DTSEC4
setenv ipaddr 10.13.11.222
setenv serverip 10.13.11.132
~~~

2. 确认连接正常

~~~
=> ping $serverip
Using FM1@DTSEC4 device
host 10.13.11.132 is alive
~~~

3. 加载文件
~~~
=> tftpboot 1000000 aa
Using FM1@DTSEC4 device
TFTP from server 10.13.11.132; our IP address is 10.13.11.222
Filename 'aa'.
Load address: 0x1000000
Loading: #
         2 KiB/s
done
Bytes transferred = 7 (7 hex)
~~~

#### kernel
1. 配置kernel ip

~~~
ifconfig eth0 192.168.5.40 netmask 255.255.255.0
route add default gw 192.168.5.1

ip addr add 192.168.17.30/24 dev eth0
ip link set eth0 up
ip route add default via 192.168.17.3
~~~
2. 从服务器下载

~~~
tftp –g –l 目标文件名 –r 源文件名 服务器地址
tftp –g –l 目标文件名 服务器地址
tftp –g  –r 源文件名 服务器地址
~~~
3. 上传给服务器

~~~
tftp –p –r 目标文件名  -l 源文件名 服务器地址
tftp –p –l 目标文件名 服务器地址
tftp –p  –r 源文件名 服务器地址
~~~

## samba

1. 安装
~~~
sudo apt-get install samba
sudo apt-get install smbclient
~~~

2. 配置匿名登录

~~~
security=share
[share]
comment=samba    ##这个是说明，随意填
path = /home/[username]/[foldername]  #这里修改为你建立的共享目录
public=yes
writable = yes
create mask=0775
directory mask=0775
available = yes
browseable = yes

forceuser=root
forcegroup=root
~~~

3. 重启服务
~~~
sudo /etc/init.d/samba restart
~~~

## nfs

#### ubuntu 
1. 安装
~~~
sudo apt-get install nfs-kernel-server nfs-common
~~~
2. 配置/etc/exports，添加
~~~
/nfsdir  *(rw,sync,no_root_squash)
~~~
3. 重启服务
~~~
sudo /etc/init.d/nfs-kernel-server restart
~~~

#### uboot
设置bootargs 为nfs, 把rootfs解压在nfs目录。
~~~
nfsboot=setenv bootargs root=/dev/nfs rw nfsroot=$serverip:$rootpath ip=$ipaddr:$serverip:$gatewayip:$netmask:$hostname:$netdev:off console=$consoledev,$baudrate $othbootargs;tftp $loadaddr $bootfile;tftp $fdtaddr $fdtfile;bootm $loadaddr - $fdtaddr

run nfsboot
~~~

#### linux

~~~
//fsl image need add busybox, no busybox will return error.
busybox mount -t nfs 10.13.11.132:/home/jcai/tftpboot/nfs nfs -o nolock
mount -t nfs 10.13.11.132:/home/jcai/tftpboot/nfs nfs -o nolock
~~~

## ftp

#### ftpget

~~~
Usage: ftpget [OPTIONS] HOST [LOCAL_FILE] REMOTE_FILE
        -c,--continue Continue previous transfer
        -v,--verbose Verbose
        -u,--username Username
        -p,--password Password
        -P,--port Port number

ftpget -u usr -p pwd  192.168.1.8 hello.txt 
~~~

#### ftpput

~~~
ftpput -u usr  -p pwd 10.10.29.209  file 
~~~

## sftp

Linux scp命令用于Linux之间复制文件和目录。

scp是 secure copy的缩写, scp是linux系统下基于ssh登陆进行安全的远程文件拷贝命令。

~~~
scp [可选参数] file_source file_target 
    -r： 递归复制整个目录。
    -P port：注意是大写的P, port是指定数据传输用到的端口号
~~~

#### 从本地复制到远程 

~~~
//命令执行后需要再输入密码
scp local_file remote_username@remote_ip:remote_file 
//命令执行后需要输入用户名和密码
scp local_file remote_ip:remote_file 
~~~

#### 从远程复制到本地 

~~~
scp  remote_username@remote_ip:remote_file local_file
//命令执行后需要输入用户名和密码
scp  remote_ip:remote_file local_file
~~~





## reference


