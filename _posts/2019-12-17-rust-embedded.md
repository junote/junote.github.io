---
layout: post
title:  "rust embedded"
date:   2019-12-17
categories: rust
tags: rust
mathjax: false
---
* content
{:toc}

## 编译环境

参照yocto 生成的工具链里有个env文件
~~~
export CC="ppce500mc-wrswrap-linux-gnu-gcc   -mcpu=e500mc -mspe=no -mno-altivec --sysroot=/vobs/ots/wrlplat/tlabqoriq50_small/build/rootfs/sdk/sysroots/tlabqoriqsmall-wrs-linux"
export CXX="ppce500mc-wrswrap-linux-gnu-g++   -mcpu=e500mc -mspe=no -mno-altivec --sysroot=/vobs/ots/wrlplat/tlabqoriq50_small/build/rootfs/sdk/sysroots/tlabqoriqsmall-wrs-linux"
export CPP="ppce500mc-wrswrap-linux-gnu-gcc -E   -mcpu=e500mc -mspe=no -mno-altivec --sysroot=/vobs/ots/wrlplat/tlabqoriq50_small/build/rootfs/sdk/sysroots/tlabqoriqsmall-wrs-linux"
~~~
在~/.cargo/config的文件里设置链接
~~~
[target.powerpc-unknown-linux-gnu]
linker = "/home/jcai/sdc1/mtera/vobs/ots/wrlplat/tlabqoriq50_small/build/rootfs/sdk/sysroots/x86_64-wrlinuxsdk-linux/usr/bin/ppce500mc-wrs-linux/powerpc-wrs-linux-gnu-gcc"
rustflags = ["-C","link-arg=--sysroot=/home/jcai/sdc1/mtera/vobs/ots/wrlplat/tlabqoriq50_small/build/rootfs/sdk/sysroots/tlabqoriqsmall-wrs-linux",
            "-C","link-arg=-mcpu=e500mc",
            "-C","link-arg=-mspe=no",
            "-C","link-arg=-mnoaltivec"
            ]
~~~

添加target
~~~
rustup target add powerpc-unknown-linux-gnu
~~~

接着用cargo 生成code并编译
~~~
cargo new hello_world
cargo build --target=powerpc-unknown-linux-gnu
~~~


## 安装

~~~
export RUSTUP_DIST_SERVER=https://mirrors.ustc.edu.cn/rust-static
export RUSTUP_UPDATE_ROOT=https://mirrors.ustc.edu.cn/rust-static/rustup
curl https://sh.rustup.rs -sSf | sh
~~~

设置cargo的源
~~~
[source.crates-io]
registry = "https://github.com/rust-lang/crates.io-index"
replace-with = 'ustc'
[source.ustc]
registry = "git://mirrors.ustc.edu.cn/crates.io-index"
~~~