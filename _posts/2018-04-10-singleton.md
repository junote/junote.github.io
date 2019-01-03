---
layout: post
title:  "Singleton单例模式"
date:   2018-04-08
categories: C++
tags: C++
mathjax: false
---
* content
{:toc}


一般情况下，我们建立的一些类是属于工具性质的，基本不用存储太多的跟自身有关的数据，在这种情况下，每次都去new一个对象，即增加了开销，也使得代码更加臃肿。其实，我们只需要一个实例对象就可以。如果采用全局或者静态变量的方式，会影响封装性，难以保证别的代码不会对全局变量造成影响。

考虑到这些需要，我们将默认的构造函数声明为私有的，这样就不会被外部所new了，甚至可以将析构函数也声明为私有的，这样就只有自己能够删除自己了。在Java和C#这样纯的面向对象的语言中，单例模式非常好实现，直接就可以在静态区初始化instance，然后通过getInstance返回，这种就被称为**饿汉式单例类**。也有些写法是在getInstance中new instance然后返回，这种就被称为**懒汉式单例类**，但这涉及到第一次getInstance的一个判断问题。

优点
1. 减少了时间和空间的开销（new实例的开销）。
2. 提高了封装性，使得外部不易改动实例。

缺点

1. 懒汉式是以时间换空间的方式。
2. 饿汉式是以空间换时间的方式。


~~~
#include <stdio.h>
class Singleton{
public:
	static Singleton* getInstance();

private:
	Singleton();	//把复制构造函数和=操作符也设为私有,防止被复制
	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);

	static Singleton* instance;
};
 
Singleton::Singleton(){

}
Singleton::Singleton(const Singleton&){

}

Singleton& Singleton::operator=(const Singleton&){

}

//在此处初始化
Singleton* Singleton::instance = new Singleton();
Singleton* Singleton::getInstance(){
	return instance;
}

int main(){
	Singleton* singleton1 = Singleton::getInstance();
	Singleton* singleton2 = Singleton::getInstance();

	if (singleton1 == singleton2)
		fprintf(stderr,"singleton1 = singleton2\n");

	return 0;
}
~~~