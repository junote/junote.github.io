---
layout: post
title:  "c++面向对象基础2"
date:   2018-04-11
categories: C++
tags: C++
mathjax: false
---
* content
{:toc}

##  转换函数 coversion Fuction

本质还是操作符重载
~~~
#include <iostream>
using namespace std;
class Fraction {
public:
	Fraction(int num,int den):m_num(num),m_den(den){}
	operator double() const { return ((double)m_num / m_den); }
private:
	int m_num, m_den;
};

int main()
{
	Fraction f(1, 2);
	double a = f + 3;
	cout << a << endl;
	double b = f + 3;
	cout << b << endl;
    return 0;
}
~~~

## explicit
用在构造函数，避免object自动转换成class。
~~~
#include <iostream>
using namespace std;
class Fraction {
public:
	//Fraction(int num,int den):m_num(num),m_den(den){}
	//Fraction(int num = 1, int den = 1) :m_num(num), m_den(den) {}
	explicit Fraction(int num = 1, int den = 1) :m_num(num), m_den(den) {}
	//operator double() const { return ((double)m_num / m_den); }
	Fraction operator+ (const Fraction f) { return Fraction(3, 3); }
private:
	int m_num, m_den;
};

int main()
{
	Fraction f(1, 2);


	Fraction  b;
	//b = f + 3; //error because different type;
	b = f + 3; //correct if default den = 1, 3 auto covert to class. 
	//commenet double too, otherwise f cover to double, but left is class.
	// if add explicit word, 3 will covert to class, error.
    return 0;
}
~~~

## pointer-like class 智能指针
重载* 和->

~~~
template<class T>
class shared_ptr
{
public:
	T& operator* () const {return *px;}
	T* operator-> () const {return px;}
	shared_ptr(T* p):px(p){}
private:
	T* px;
	long* pn;
};
~~~

## fuction-like class 仿函数
实现一个operator()，在类实例化时，就将要用的，非参数的元素传入类中。

要使用STL内建的仿函数，必须包含\<functional\>头文件。


~~~
    #include <iostream>  
    #include <algorithm>  
      
    using namespace std;  
    template<typename T>  
    class display  
    {  
    public:  
        void operator()(const T &x)  
        {  
            cout<<x<<" ";   
        }   
    };   
      
      
    int main()  
    {  
        int ia[]={1,2,3,4,5};  
        for_each(ia,ia+5,display<int>());   
          
        return 0;   
    }   
~~~

## 成员模板Member templates

~~~
#include <iostream>
#include <vector>
#include <algorithm>
 
struct Printer { // generic functor
    std::ostream& os;
    Printer(std::ostream& os) : os(os) {}
    template<typename T>
    void operator()(const T& obj) { os << obj << ' '; } // member template
};
 
int main()
{
    std::vector<int> v = {1,2,3};
    std::for_each(v.begin(), v.end(), Printer(std::cout));
    std::string s = "abc";
    std::for_each(s.begin(), s.end(), Printer(std::cout));
}
~~~

## 成员函数模板Member function templates
~~~
template<typename T>
struct A {
    void f(int); // non-template member
 
    template<typename T2>
    void f(T2); // member template
};
 
//template member definition
template<typename T>
template<typename T2>
void A<T>::f(T2)
{
    // some code
}
 
int main()
{
    A<char> ac;
    ac.f('c'); // calls template function A<char>::f<char>(int)
    ac.f(1);   // calls non-template function A<char>::f(int)
    ac.f<>(1); // calls template function A<char>::f<int>(int)
}
~~~
## 模板特化 specializaiotn

实际上就是模块的重载
~~~
#include <iostream>
#include <cstring>
#include <cmath>
// general version
template<class T>
class Compare
{
public:
    static bool IsEqual(const T& lh, const T& rh)
    {
        std::cout <<"in the general class..." <<std::endl;
        return lh == rh;
    }
};



// specialize for float
template<>
class Compare<float>
{
public:
    static bool IsEqual(const float& lh, const float& rh)
    {
        std::cout <<"in the float special class..." <<std::endl;

        return std::abs(lh - rh) < 10e-3;
    }
};

// specialize for double
template<>
class Compare<double>
{
public:
    static bool IsEqual(const double& lh, const double& rh)
    {
        std::cout <<"in the double special class..." <<std::endl;

        return std::abs(lh - rh) < 10e-6;
    }
};


int main(void)
{
    Compare<int> comp1;
    std::cout <<comp1.IsEqual(3, 4) <<std::endl;
    std::cout <<comp1.IsEqual(3, 3) <<std::endl;

    Compare<float> comp2;
    std::cout <<comp2.IsEqual(3.14, 4.14) <<std::endl;
    std::cout <<comp2.IsEqual(3, 3) <<std::endl;

    Compare<double> comp3;
    std::cout <<comp3.IsEqual(3.14159, 4.14159) <<std::endl;
    std::cout <<comp3.IsEqual(3.14159, 3.14159) <<std::endl;
    return 0;
}
~~~

## partial specialization

函数模版不存在偏特化，只有类模版才能偏特化

全特化:
~~~
template<> 
class Template<int,char>{};
~~~
偏特化：
~~~
template<class T> 
class Template<T,int>{};
~~~

## 模板模板参数  template template parameter

模板的第一个参数是T类型，第二个参数是一个Container，他是一个可以指定一个U类型的变量。
~~~
template<typename T, template<typename U> typename Container>
class XCls
{
    private:
        Container<T> c;
};

template<typename T>
using Lst = std::list<T, std::allocator<T>>;

XCls<std::string, Lst> mylst2;
~~~

## 可变模板参数 variadic template(C++11)

语法 typename...
函数里调用参数都要加...

~~~
#include <iostream>
#include <bitset>
using namespace std;

void print()
{}
template<typename T, typename... Types>
void print(const T& firstArgs, const Types&... args)
{
	cout << firstArgs << endl;
	cout << "args num = " << sizeof...(args) << endl;
	print(args...);
}

int main()
{
	print(4.3, "sss", 43, bitset<16>(15));
}

~~~

## auto 

必须后面紧跟value，不能直接定义一个变量为auto

~~~
	auto i = 1;
	cout << i << endl;
	auto s = "sss";
	cout << s << endl;
~~~

## ranged-base for

语法： for(dec: coll){}

## const 

当成员函数的const和no-const函数同时存在时，constobject只能调用const版本，no-const只能调用no-const。
||const object| non-const object|
|-|:-:|:-:|
|const member fun(data const)|OK|OK|
|non-const member fun(data variable)|NOK|OK|

