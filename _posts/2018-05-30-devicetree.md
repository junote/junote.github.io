---
layout: post
title:  "devicetree"
date:   2018-05-30
categories: linux
tags: embedded linux
mathjax: false
---
* content
{:toc}

Device Tree由一系列被命名的结点（node）和属性（property）组成，而结点本身可包含子结点。所谓属性，其实就是成对出现的name和value。在Device Tree中，可描述的信息包括（原先这些信息大多被hard code到kernel中）：

- CPU的数量和类别
- 内存基地址和大小
- 总线和桥
- 外设连接
- 中断控制器和中断使用情况
- GPIO控制器和GPIO使用情况
- Clock控制器和Clock使用情况

## 基本
~~~
    / {  
        node1 {  
            a-string-property = "A string";  
            a-string-list-property = "first string", "second string";  
            a-byte-data-property = [0x01 0x23 0x34 0x56];  
            child-node1 {  
                first-child-property;  
                second-child-property = <1>;  
                a-string-property = "Hello, world";  
            };  
            child-node2 {  
            };  
        };  
        node2 {  
            an-empty-property;  
            a-cell-property = <1 2 3 4>; /* each number (cell) is a uint32 */  
            child-node1 {  
            };  
        };  
    };  
~~~

#### Node Names
除root节点名用'/'表示外，其余节点都由node-name@unit-address来命名，且同一层级必须是唯一的。

- **node-name**

    表示节点名，由1-31个字符组成。如非必须，推荐使用以下通用的node-name: 
    cpu、memory、memory-controller、gpio、serial、watchdog、flash、compact-flash、rtc、interrupt-controller、dma-controller、ethernet、ethernet-phy、timer、mdio、spi、i2c、usb、can、keyboard、ide、disk、display、sound、atm、cache-controller、crypto、fdc、isa、mouse、nvram、parallel、pc-card、pci、pcie、sata、scsi、vme。

-    **unit-address**

    表示这个节点所在的bus类型。它必须和节点中reg属性的第一个地址一致。如果这个节点没有reg属性，则不需“@"
#### Path Names
表示一个节点的完整路径（full path）。型如：

    /node-name-1/node-name-2/node-name-N
#### Properties
每个节点包含的主要内容就是这个所描述的设备的属性信息，由name和value组成：

- **Property Names**

    1-31个字符，可包含字母、数字、及‘,’，‘.’，‘_’，‘+’，‘?’，‘#’。

- **Property Values**

|Value|	Description|
|-|:-:|
|empty| 	属性值为空，用来表示true-false信息|
|u32/u64| 	32/64位大端字节序的无符号整形，表示时需加<>|
|string,stringlist| 	null-terminated字符串或其组成的列表|

## Standard Properties
#### compatible
表示兼容的设备类型，内核据此选择合适的驱动程序。由多个字符串组成，从左到由列出这个设备兼容的驱动（from most specific to most general）。 推荐的格式为：“制造商名,具体型号”。

    compatible = "fsl,mpc8641-uart", "ns16550";
    内核先搜索支持“fsl,mpc8641-uart”的驱动，如未找到，则搜索支持更通用的“ns16550”设备类型的驱动。
#### model
表明设备型号。    推荐的格式为：“制造商名,具体型号”。

    model = "fsl,MPC8349EMITX";
#### phandle
用一个树内唯一的数字标识所在的这个节点，其他节点可以直接通过这个数字标识来引用这个节点。
~~~
    pic@10000000 {
        phandle = <1>;
        interrupt-controller;
    };
    interrupt-parent = <1>;
~~~

#### status
- 表示设备的可用状态：
- "okay" -> 设备可用
- "disabled" -> 目前不可用，但以后可能会可用
- "fail" -> 不可用。出现严重问题，得修一下
- "fail-sss" -> 不可用。出现严重问题，得修一下。sss指明错误类型。
#### #address-cells and #size-cells
在拥有子节点的节点中使用，来描述它的字节点的地址分配问题。即分别表示子节点中使用多少个u32大小的cell来编码reg属性中的address域和size域。

这两个属性不会继承，必须明确指出。如未指出，默认#address-cells=2，#size-cells=1。

每个address是1个cell（32bit），且每个长度值也是一个cell。在32位系统中#size-cells通常就是这样设置为1的。而在64位系统中，#address-cells和#size-cells则通常设置为2。

#### reg
描述该设备在parent bus定义的地址空间中的地址资源分配。
~~~
reg = <0x3000 0x20 0xFE00 0x100>;
a 32-byte block at offset 0x3000 and a 256-byte block at offset 0xFE00。

    external-bus {
        #address-cells = <2>
        #size-cells = <1>;
        ethernet@0,0 {
            compatible = "smc,smc91c111";
            reg = <0 0 0x1000>;
        };
    }
external-bus使用了两个cell来描述address；一个表示片选号，另一个表示与片选基地址间的偏移量。length区域则用了一个cell来描述。在这个例子中，每个reg节点包含3个cell，分别是：片选号，偏移量，长度
~~~
#### ranges
提供了子地址空间与父地址空间的映射关系，如果值为空则父子地址相等，无需转换。
~~~
    soc {
        compatible = "simple-bus";
        #address-cells = <1>;
        #size-cells = <1>;
        ranges = <0x0 0xe0000000 0x00100000>;

        serial {
            compatible = "ns16550";
            reg = <0x4600 0x100>;
        };
    };
~~~
将子节点serial的0x0地址映射到父节点soc的0xe0000000，映射长度为0x100000。此时reg的实际物理地址就为0xe0004600。


#### interrupts

 -  interrupt-controller - 一个空的属性定义(就是仅仅列出了该字符串,见下面)  , 该节点作为一个接收中断信号的设备。

 -  #interrupt-cells - 这是一个中断控制器节点的属性。它声明了该中断控制器的中断指示符中 cell 的个数（类似于 #address-cells 和 #size-cells）。

 -  interrupt-parent - 这是一个设备节点的属性，包含一个指向该设备连接的中断控制器的 phandle。那些没有 interrupt-parent 的节点则从它们的父节点中继承该属性。

 - interrupts - 一个设备节点属性，包含一个中断指示符的列表，对应于该设备上的每个中断输出信号。
interrupts = <   >这个里面的是1个数，有的是2个数，有的是3个数。
一个cell的情况：

当前interrupt 位于他的中断控制器的索引，比如：
~~~
    vic: intc@10140000 {
        compatible = "arm,versatile-vic";
        interrupt-controller;
        #interrupt-cells = <1>;
        reg = <0x10140000 0x1000>;
    };  


    sic: intc@10003000 {
        compatible = "arm,versatile-sic";
        interrupt-controller;
        #interrupt-cells = <1>;
        reg = <0x10003000 0x1000>;
        interrupt-parent = <&vic>;
        interrupts = <31>; /* Cascaded to vic */
    };
~~~

二个cell的情况

第一个值： 该中断位于他的中断控制器的索引；

第二个值：触发的类型

固定的取值如下：

        1 = low-to-high edge triggered
        2 = high-to-low edge triggered
        4 = active high level-sensitive
        8 = active low level-sensitive


三个cell的情况

第一个值：中断号

第二个值：触发的类型

第三个值：优先级，0级是最高的，7级是最低的；其中0级的中断系统当做 FIQ处理。

## Base Device Node Types
所有的设备树都必须有一个root节点，且root节点下必须包含一个cpus节点和至少一个memory节点。
- root node,root节点须包含 #address-cells、#size-cells、model、compatible等属性。
- cpus node, 是cpu子节点的父节点容器。须包含 #address-cells、#size-cells属性。
- /cpus/cpu* node 是描述系统cpu的节点
- memory node 描述系统物理内存的layout。须包含reg节点。
~~~
假如一个64位系统有如下两块物理内存：
- RAM: starting address 0x0, length 0x80000000 (2GB)
- RAM: starting address 0x100000000, length 0x100000000 (4GB)
则我们可以有下面两种描述方法
#address-cells = <2> 
#size-cells =<2>
Example #1
    memory@0 {
        reg = <0x000000000 0x00000000 0x00000000 0x80000000
               0x000000001 0x00000000 0x00000001 0x00000000>;
    };
Example #2
    memory@0 {
        reg = <0x000000000 0x00000000 0x00000000 0x80000000>;
    };
    memory@100000000 {
        reg = <0x000000001 0x00000000 0x00000001 0x00000000>;
    };
~~~
- chosen node 根节点下的一个子节点，不是描述设备而是描述运行时参数。常用来给内核传递bootargs:
~~~
chosen {
    bootargs = "root=/dev/nfs rw nfsroot=192.168.1.1 console=ttyS0,115200";
};
~~~
- aliases node 由1-31个字母、数字或下划线组成的设备节点full path的别名。它的值是节点的全路径，因此最终会被编码成字符串。
~~~
    aliases {
        ethernet0 = &eth0;
        serial0 = &serial0;
        serial0 = "/simple-bus@fe000000/serial@llc500";
    };
~~~

1. [Device Tree Usage](https://elinux.org/Device_Tree_Usage)
2. [standard](www.power.org/resources/downloads/Power_ePAPR_APPROVED_v1.0.pdf)
3. [devicetree(设备树)的用法](https://blog.csdn.net/hpu11/article/details/54965020)
4. [Linux设备驱动之devicetree](https://www.linuxidc.com/Linux/2016-12/138208.htm)
