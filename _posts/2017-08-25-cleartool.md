---
layout: post
title:  "cleartool"
date:   2017-08-25
categories: linux 
tags: cleartool
mathjax: true
---
* content
{:toc}


|命令|作用| 
|-|:-:| 
|cleartool co -nc xxx.cpp|checkout xxx.cpp| 
|cleartool ci -nc xxx.cpp |checkin xxx.cpp| 
|cleartool mkdir -c comment new_dir|left/down/up/right window| 
|cleartool mkelem -c comment new_file.cpp|comment mutiline| 
|cleartool lsvtree file.cpp|查看最新版本| 
|||
|cleartool mkview –tag test1 /ccvob/views/test1.vws|创建view|
|cleartool rmview  –tag test1|删除view|
|||
|cleartool catcs -tag your_view_name|查看view配置| 
|cleartool edcs -tag your_view_name|修改配置文件| 
|clearfsimport -recurse /xxx/xxx/xxx/src /view/zhuj/home/vobs/cc_account|导入文件夹 | 

