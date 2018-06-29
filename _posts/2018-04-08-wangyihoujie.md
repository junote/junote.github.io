---
layout: post
title:  "c++面向对象基础"
date:   2018-04-08
categories: C++
tags: C++
mathjax: false
---
* content
{:toc}

##  没有指针的class 

complex
~~~
#ifndef __COMPLEX__
#define __COMPLEX__
#include <iostream>
class complex {
public:
	complex(double r = 0, double i = 0)
		: rv(r),iv(i){}
	double real() const { return rv; }
	double imag() const { return iv; }
	complex& operator += (const complex& rhs);
	
private:
	double rv, iv;
	friend complex& __iadd(complex *ths, const complex rhs);
};

inline complex& __iadd(complex *ths, const complex rhs)
{
	ths->rv += rhs.rv;
	ths->iv += rhs.iv;
	return *ths;
}

complex& complex::operator += (const complex& rhs)
{
	return __iadd(this, rhs);
}

complex operator + (const complex& a, const complex& b)
{
	return complex(a.real() + b.real(),
		a.imag() + b.imag());
}
std::ostream& operator << (std::ostream& os, const complex& x)
{
	return os << "(" << x.real() << "," << x.imag() << ")";
}
#endif // !__COMPLEX__
~~~
1. 构造函数使用init来初始化。
2. 数据变量放在private里。
3. 尽量使用reference来传递，少用value，提高读写速度。
4. 参数如果不需更改，添加const来限制，这样函数和主程序都无法更改。
5. 返回值尽量使用reference。
6. 如果返回一个函数创造的变量，那么返回的应该是value，同时应该定义成非成员函数。
7. friend可以用来直接读取class的private变量。
8. this指针是隐藏在class里的，无需再函数里定义。
9. 操作符重载需要注意连续赋值，比如上例<<如果是返回void，那么cout<<complea << endl就无法工作。
10. 相同class的各个object互为friend，比如public里+重载，获取其他rhs的private变量。
11. 传递参数时无需知道接收方以reference接收
12. 要用ifnedf来保护h文件。

## 有指针的class 

MyString

~~~
#include <cstring>
#include <iostream>

using namespace std;

class MyString
{
public:
	MyString(const char* mdata );
	MyString(const MyString& s);
	MyString& operator= (const MyString s);
	~MyString();
	char* get_c_str() const { return m_data; }
private:
	char* m_data;
};

inline MyString::MyString(const char *mdata = 0)
{
	if (mdata) {
		m_data = new char[strlen(mdata) + 1];
		strcpy(m_data, mdata);
	}
	else{
		m_data = new char[1];
		*m_data = '\0';
	}
}
inline MyString::~MyString()
{
	delete[] m_data;
}
inline MyString::MyString(const MyString& s)
{
	m_data = new char[strlen(s.m_data) + 1];
	strcpy(m_data, s.m_data);
}
inline MyString& MyString::operator= (const MyString s)
{
	if (this == &s)
		return *this;
	delete[] m_data;
	m_data = new char[strlen(s.m_data) + 1];
	strcpy(m_data, s.m_data);
	return *this;
}
std::ostream& operator<< (std::ostream& os, MyString s)
{
	return os << s.get_c_str();
}
int main()
{
	MyString s("hello");
	cout << s << endl;
	MyString s2(s);
	cout << "s2 = " << s2 << endl;
	MyString s3 = s2;
	cout << "s3 = " << s3 << endl;
    return 0;
}
~~~

1. new在构造函数中申请内存，delete 在析构函数清理。
2. three big 三大函数分别为拷贝构造函数、拷贝赋值函数和析构函数。



## stack heap
1. stack栈存在于作用域scope的一块地址空间，例如调用函数就会形成一个stack，用来放置参数，内部变量和返回地址。
2. heap堆是系统提供的一块地址空间，程序可以动态提供。
3. staic的作用域在函数结束后仍然存在，直到程序结束。
4. 全局变量直到程序结束。
5. memory leak内存泄漏是指作用域结束后，heap的对象仍然存在。

# static 函数
1. static 函数没有this指针。
2. static 数据必须看做全局函数设定。
3. static 函数可以通过class直接设定，或者object设置。
~~~
#include <iostream>

using namespace std;

class Account {
public:
	static double m_rate;
	static void set_rate(const double rate);
};
double Account::m_rate = 8.0;
void Account::set_rate(const double rate)
{
	m_rate = rate;
}
int main()
{
	Account::set_rate(5.0);

	Account a;
	a.set_rate(3.0);
    return 0;
}
~~~

## static  和 Singleton

~~~
#include <iostream>

class A {
public:
	static A  GetInstance() { static A a; return a; }
private:
	A(){}
	A(const A& rhs);
};

int main()
{
    return 0;
}
~~~

## template

template 类 

~~~
template<typename T>
class complex {}
~~~
template 函数
~~~
template <class T>
T& fuc(const T& a,const T& b){}
~~~
example：
~~~
#include <iostream>

template<typename T>
class complex {
public:
	complex(T r = 0, i = 0) :re(r), im(i) {}
	T real() { return re; }
	T imag() { return im; }
	bool operater < (const complex& rhs) const
	{
		return (this->re * this->re + this->im * this->im) <
			(rhs.re * rhs.re + rhs.im + rhs.im);
	}
private:
	T re, im;
};

template <class T>
inline const T& min(const T& a,const T&)
{
	return b < a ? b : a;
}

int main()
{
	complex<int> a(1, 1);
	complex<int> a2(1, 2);
	complex<double> b(3, 5.0);
	complex<int> c;
	c = min(a, a2);
    return 0;
}

~~~

## composition 复合
1. 一个class包含另外一个class，但是不含指针。
2. has-a
3. 构造由内而外，析构由外而内。

~~~
template <typename  T>
class queue {
protect:
    deque<T> c;
...
};

template <typename T>
class deque {
protect:
    Iter<T> start;
    Iter<T> finish;
    T** map;
    unsigned int map_size;
...
};

template <typename T>
struct Iter{
    T* cur;
    T* first;
    T* last;
    T* node;
....
};
~~~

## Delegation委托  composition by reference

包含带指针的class

~~~
class String{
public：
    String();
    String(const char* s);
    String(const String& s);
    String& operator= (const String& s);
    ~String();
private:
    StringRep* rep;
}；

class StringRep{
    friend class String;
    StringRep(const char* s);
    ~StringRep();
    int count;
    char *rep;
};
~~~

## Inheritance 继承
1. is-a
2. base class 的析构函数必须是virtual。
3. 构造由内到外，析构由外到内。
~~~
struct base{
    base* next;
    base* prev;
}；
template<typename T>
struct node: public base
{
    T data;
};
~~~

## 虚函数
1. virtual函数，子函数可以重新定义，同时父类已有默认定义。
2. pure virtual 函数，子函数必须重新定义，父类没有默认定义。
~~~
class shape{
public:
    virtual void draw() const = 0;//pure virtual
    virtual void error(const std::string msg);
    virtual ~shape();
};
class Rectangle：public shape
{
    virtual void draw() const;
};
~~~

