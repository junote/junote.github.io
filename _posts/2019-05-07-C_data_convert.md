---
layout: post
title:  "C 语言数据传唤"
date:   2019-05-07
categories: C
tags: C
mathjax: false
---
* content
{:toc}

### 根据地址转换

~~~
#include <stdio.h>
int main()
{

    unsigned char a[10]={1,2,3,4,5,6,7,8,9,0};
    unsigned int b = 0x06070809;

    unsigned int *addr;
    int i;

    addr = (unsigned int *)(&a[0]);
    *addr = b;


    for (i = 0; i < 10; i++)
        printf("%d\t",a[i]);

    return 0;
}
~~~



因为是小端，结果：
~~~
[test]$ ./a.out
9   8   7   6   5   6   7   8   9   0
~~~

### 利用union

~~~
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef union {
    unsigned int a;
    unsigned char b[4];
}aa;


int main()
{
    aa abc;
    int i;
    abc.a = 0x12345678;
    for(i = 0; i < 4; i++)
        printf("%x\t",abc.b[i]);
    printf("\n");
}
~~~
结果：
~~~
78      56      34      12
~~~

