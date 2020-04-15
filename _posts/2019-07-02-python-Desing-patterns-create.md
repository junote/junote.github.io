---
layout: post
title:  "python设计模式-创建型"
date:   2019-07-02
categories: python
tags: python
mathjax: false
---
* content
{:toc}

模式|一句话
-|-
抽象工厂|复杂对象由许多小对象组成
工厂|表示一个负责创建其他类型对象的类
建造者|创建由其他对象组合而成的复杂对象，保留细节
原型|根据现有对象复制新的对象并进行修改
单例|单例类只有一个实例

## Factory Method（工厂方法）

在面向对象编程中，术语“工厂”表示一个负责创建其他类型对象的类。通常情况下，作为一个工厂的类有一个对象以及与它关联的多个方法。客户端使用某些参数调用此方法，之后，工厂会据此创建所需类型的对象，然后将它们返回给客户端。

定义一个用于创建对象的接口，让子类决定实例化哪一个类。Factory Method 使一个类的实例化延迟到其子类。

适用性：
* 当一个类不知道它所必须创建的对象的类的时候。
* 当一个类希望由它的子类来指定它所创建的对象的时候。
* 当类将创建对象的职责委托给多个帮助子类中的某一个，并且你希望将哪一个帮助子类是代理者这一信息局部化的时候。
~~~
class chineseGetter:
    """A simple localizer a la gettext"""
    def __init__(self):
        self.trans = dict(dog=u"小狗", cat=u"小猫")
 
    def get(self, msgid):
        """We'll punt if we don't have a translation"""
        try:
            return self.trans[msgid]
        except KeyError:
            return str(msgid)
 
 
class EnglishGetter:
    """Simply echoes the msg ids"""
    def get(self, msgid):
        return str(msgid)
 
 
def get_localizer(language="English"):
    """The factory method"""
    languages = dict(English=EnglishGetter, chinese=chineseGetter)
    return languages[language]()
 
# Create our localizers
e, g = get_localizer("English"), get_localizer("chinese")
# Localize some text
for msgid in "dog parrot cat bear".split():
    print(e.get(msgid), g.get(msgid))
~~~
## Abstract Factory（抽象工厂）

主要目的是提供一个接口来创建一系列相关对象，而无需指定具体的类。工厂方法将创建实例的任务委托给了子类，而抽象工厂方法的目标是创建一系列相关对象。

提供一个创建一系列相关或相互依赖对象的接口，而无需指定它们具体的类。 

适用性：
* 一个系统要独立于它的产品的创建、组合和表示时。
* 一个系统要由多个产品系列中的一个来配置时。
* 当你要强调一系列相关的产品对象的设计以便进行联合使用时。
* 当你提供一个产品类库，而只想显示它们的接口而不是实现时。

~~~
#!/usr/bin/python
#coding:utf8
'''
Abstract Factory
'''
 
import random
 
class PetShop:
    """A pet shop"""
 
    def __init__(self, animal_factory=None):
        """pet_factory is our abstract factory.
        We can set it at will."""
 
        self.pet_factory = animal_factory
 
    def show_pet(self):
        """Creates and shows a pet using the
        abstract factory"""
 
        pet = self.pet_factory.get_pet()
        print("This is a lovely", str(pet))
        print("It says", pet.speak())
        print("It eats", self.pet_factory.get_food())
 
 
# Stuff that our factory makes
 
class Dog:
    def speak(self):
        return "woof"
 
    def __str__(self):
        return "Dog"
 
 
class Cat:
    def speak(self):
        return "meow"
 
    def __str__(self):
        return "Cat"
 
 
# Factory classes
 
class DogFactory:
    def get_pet(self):
        return Dog()
 
    def get_food(self):
        return "dog food"
 
 
class CatFactory:
    def get_pet(self):
        return Cat()
 
    def get_food(self):
        return "cat food"
 
 
# Create the proper family
def get_factory():
    """Let's be dynamic!"""
    return random.choice([DogFactory, CatFactory])()
 
 
# Show pets with various factories
if __name__ == "__main__":
    shop = PetShop()
    for i in range(3):
        shop.pet_factory = get_factory()
        shop.show_pet()
        print("=" * 20)
~~~

## Builder（建造者）

将一个复杂对象的构建与它的表示分离，使得同样的构建过程可以创建不同的表示。

适用性：
* 当创建复杂对象的算法应该独立于该对象的组成部分以及它们的装配方式时。
* 当构造过程必须允许被构造的对象有不同的表示时。

与抽象工厂类似，都可以创建多个对象组成的复杂对象，区别在于它不仅提供创建复杂对象的方法，还保留了细节。
另外，抽象工厂特别适用于需要把复杂对象各部分的细节与其创建流程相分离的场合。

~~~
#!/usr/bin/python
#coding:utf8
 
"""
    Builder
"""
 
# Director
class Director(object):
    def __init__(self):
        self.builder = None
 
    def construct_building(self):
        self.builder.new_building()
        self.builder.build_floor()
        self.builder.build_size()
 
    def get_building(self):
        return self.builder.building
 
 
# Abstract Builder
class Builder(object):
    def __init__(self):
        self.building = None
 
    def new_building(self):
        self.building = Building()
 
 
# Concrete Builder
class BuilderHouse(Builder):
    def build_floor(self):
        self.building.floor = 'One'
 
    def build_size(self):
        self.building.size = 'Big'
 
 
class BuilderFlat(Builder):
    def build_floor(self):
        self.building.floor = 'More than One'
 
    def build_size(self):
        self.building.size = 'Small'
 
 
# Product
class Building(object):
    def __init__(self):
        self.floor = None
        self.size = None
 
    def __repr__(self):
        return 'Floor: %s | Size: %s' % (self.floor, self.size)
 
 
# Client
if __name__ == "__main__":
    director = Director()
    director.builder = BuilderHouse()
    director.construct_building()
    building = director.get_building()
    print(building)
    director.builder = BuilderFlat()
    director.construct_building()
    building = director.get_building()
    print(building)
~~~
## Prototype（原型）

用原型实例指定创建对象的种类，并且通过拷贝这些原型创建新的对象。

适用性：

当要实例化的类是在运行时刻指定时，例如，通过动态装载；或者为了避免创建一个与产品类层次平行的工厂类层次时；或者当一个类的实例只能有几个不同状态组合中的一种时。建立相应数目的原型并克隆它们可能比每次用合适的状态手工实例化该类更方便一些。

~~~
class Point:
    __slot__ = ("x","y")
    def __init__(self, x, y):
        self.x = x
        self.y =y

def make_object(Class, *args, **kwargs):
    return Class(*args, **kwargs)

point1 = Point(1,2)
point2 = make_object(Point, 5, 10)
point3 = copy.deepcopy(point1)
point4 = point1.__class__(7,14)
~~~

## Singleton（单例）

保证一个类仅有一个实例，并提供一个访问它的全局访问点。

适用性：

当类只能有一个实例而且客户可以从一个众所周知的访问点访问它时。

当这个唯一实例应该是通过子类化可扩展的，并且客户应该无需更改代码就能使用一个扩展的实例时。

~~~
class Singleton(object):
    ''''' A python style singleton '''
 
    def __new__(cls, *args, **kw):
        if not hasattr(cls, '_instance'):
            org = super(Singleton, cls)
            cls._instance = org.__new__(cls, *args, **kw)
        return cls._instance

class SingleSpam(Singleton):
    def __init__(self, s):
            self.s = s
 
    def __str__(self):
            return self.s

a = SingleSpam('a')
b = a


In [31]: a = SingleSpam('a')

In [32]: b = a

In [35]: a
Out[35]: <__main__.SingleSpam at 0x7f879149d9e8>

In [36]: b
Out[36]: <__main__.SingleSpam at 0x7f879149d9e8>

~~~

元类实现方法
~~~
class MetaSingleton( type): 
	_instances = {} 
	def __call__( cls, *args, **kwargs): 
		if cls not in cls._ instances: 
			cls._ instances[ cls] = super( MetaSingleton,  cls). __call__(* args, **kwargs) 
		return cls._ instances[ cls] 

class Logger( metaclass= MetaSingleton): 
	pass 
logger1 = Logger() 
logger2 = Logger() 
print( logger1, logger2)
~~~