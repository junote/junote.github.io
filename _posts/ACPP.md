---
layout: post
title:  "Anvanced C++"
date:   2017-04-02
categories: C++
tags: C++11 
mathjax: false
---
* content
{:toc}

##  const

~~~
//  A compiler constraint that an object can not be modiied

int main()
{
    const int i = 9;
  //  i = 10; // error

  const int *p1 = &i; //data is const, point is not;
  p1++;

  int* const p2; // point is const,data is not;

  const int* const p3; // point and data are const.

 //if const on the left of *, data is const;
 //if const on right of *, point is const; 

 const_cast<int&>(i)  = 6; //const_cast delet const;

 int j ;
 static_cast<cost int&>(j) = 7;
}
~~~ 


## const and Functions

~~~
#include <iostream>
using namespace std;

class Dog {
	int age;
	string name;
public:
	Dog() { age = 3; name = "demmy"; }

	//const parameters
	//void setAge(int& a) { age = a; a++; } 
	void setAge(const int& a) { age = a;} 

	// const return value
	const string& getName() { return name; }

	//const fuc
	void printDogName()  const;
};

void Dog::printDogName() const {
	//age++;  not work;
}

int main()
{
	Dog d;
	int i = 9;
	d.setAge(i);
	cout << i << endl; // i change to 10 if no const;

	const string& n = d.getName();

	d.printDogName();
    return 0;
}
~~~

## Logic Constness and Bitwise Constness
~~~
#include "stdafx.h"
#include <iostream>
#include <vector>
using namespace std;

class BigV {
	vector<int> v;
	mutable int accessCounter;
	//int accessCounter;

	int* v2;
public:
	int getItem(int index) const {
		accessCounter++; // const fuc can not change class private, add mutable or cast it;
		//const_cast<BigV*>(this)->accessCounter++;
		return v[index];
	}

	void setV2Item(int index, int x) const { // actually it is not a const func
		*(v2 + index) = x;
	}
};

int main()
{
    return 0;
}
~~~

##　Compiler Generated Functions

~~~
class Dog{};

//compiler will generate:

class Dog {
    public:
        Dog(const Dog& rhs) {}; // member by member initialization
        Dog& operater=(const Dog& rhs){}; //member by member copying
        Dog() {};// call base class's default constructor;
                // call data member's default constructor;
        ~Dog(){}; // call base class default destructor;
                  // call data member destructor;
};
~~~

defualt constructor in c++11
~~~
class dog {
    public:
        dog() = default;
        dog(string name) {}
};
~~~

## Disallow Functions

在C++03的标准里面，如果程序代码里面没有写默认构造函数(像cv();)、复制构造函数、复制赋值函数(像cv cv2=cv1;)和析构函数，则编译器会自动添加这些函数。当程序里面写了构造函数的时候，编译器就不会自动添加默认构造函数了。

C++11里面可以用default来指定使用默认的构造函数，而且可以通过delete来显式地禁止一些方法
~~~
struct NonCopyable{
	NonCopyable() = default;
	NonCopyable(const NonCopyable&) = delete;
	NonCopyable& operator=(const NonCopyable&) = delete;
};
~~~

第一条语句是强制编译器生成默认构造函数作为struct的构造函数；第2、3条语句就是显式地禁用复制构造函数和复制赋值函数。 

既然禁止了复制构造函数，那么如果想通过已经生成的类的实例来初始化一个同类的实例，要怎么操作呢？显然，cv cv2(cv1)和cv cv2=cv1;是不可以用的了，因为复制构造函数已经被禁止了。

C++11新定义了一个叫做move constructor的构造函数，签名方法如下：

~~~

class_name c1;
class_name c2=std::move(c1);
class_name c3(std:move(c1));

~~~

~~~
#include <iostream>
#include <utility>
#include <vector>
#include <string>
 
int main()
{
    std::string str = "Hello";
    std::vector<std::string> v;
 
    // 使用 push_back(const T&) 重载，
    // 表示我们将带来复制 str 的成本
    v.push_back(str);
    std::cout << "After copy, str is \"" << str << "\"\n";
 
    // 使用右值引用 push_back(T&&) 重载，
    // 表示不复制字符串；而是
    // str 的内容被移动进 vector
    // 这个开销比较低，但也意味着 str 现在可能为空。
    v.push_back(std::move(str));
    std::cout << "After move, str is \"" << str << "\"\n";
 
    std::cout << "The contents of the vector are \"" << v[0]
                                         << "\", \"" << v[1] << "\"\n";
}
~~~

output:

~~~
After copy, str is "Hello"
After move, str is ""
The contents of the vector are "Hello", "Hello"
~~~

