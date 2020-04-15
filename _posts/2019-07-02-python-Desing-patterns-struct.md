---
layout: post
title:  "python设计模式-结构型"
date:   2019-07-02
categories: python
tags: python
mathjax: false
---
* content
{:toc}

模式|一句话
-|-
适配器|接口适配，一个类使用不兼容的类
桥接|抽象 与实现方式相隔离
修饰器|动态地给一个对象添加一些额外的职责。
外观|提供一个高层次的接口，使得子系统通过一个统一的对象进行通信。
享元|多个小对象相同，可以给每个对象只创建一个实例
代理|一个对象代表另一个对象

## Adapter Class/Object（适配器）

适配器模式定义如下：将一个类的接口变换成客户端期待的另一种接口，从而使原本因接口不匹配而无法在一起工作的两个类能够在一起工作。适配器模式和装饰模式有一定的相似性，都起包装的作用，但二者本质上又是不同的，装饰模式的结果，是给一个对象增加了一些额外的职责，而适配器模式，则是将另一个对象进行了“伪装”。

将一个类的接口转换成客户希望的另外一个接口。Adapter 模式使得原本由于接口不兼容而不能一起工作的那些类可以一起工作。 

适用性：

* 你想使用一个已经存在的类，而它的接口不符合你的需求。
* 你想创建一个可以复用的类，该类可以与其他不相关的类或不可预见的类（即那些接口可能不一定兼容的类）协同工作。
* 你想使用一些已经存在的子类，但是不可能对每一个都进行子类化以匹配它们的接口。对象适配器可以适配它的父类接口。


假设某公司A与某公司B需要合作，公司A需要访问公司B的人员信息，但公司A与公司B协议接口不同，该如何处理？先将公司A和公司B针对各自的人员信息访问系统封装了对象接口。
~~~
class ACpnStaff:
    name=""
    id=""
    phone=""
    def __init__(self,id):
        self.id=id
    def getName(self):
        print "A protocol getName method...id:%s"%self.id
        return self.name
    def setName(self,name):
        print "A protocol setName method...id:%s"%self.id
        self.name=name
    def getPhone(self):
        print "A protocol getPhone method...id:%s"%self.id
        return self.phone
    def setPhone(self,phone):
        print "A protocol setPhone method...id:%s"%self.id
        self.phone=phone
class BCpnStaff:
    name=""
    id=""
    telephone=""
    def __init__(self,id):
        self.id=id
    def get_name(self):
        print "B protocol get_name method...id:%s"%self.id
        return self.name
    def set_name(self,name):
        print "B protocol set_name method...id:%s"%self.id
        self.name=name
    def get_telephone(self):
        print "B protocol get_telephone method...id:%s"%self.id
        return self.telephone
    def set_telephone(self,telephone):
        print "B protocol get_name method...id:%s"%self.id
        self.telephone=telephone


class CpnStaffAdapter:
    b_cpn=""
    def __init__(self,id):
        self.b_cpn=BCpnStaff(id)
    def getName(self):
        return self.b_cpn.get_name()
    def getPhone(self):
        return self.b_cpn.get_telephone()
    def setName(self,name):
        self.b_cpn.set_name(name)
    def setPhone(self,phone):
        self.b_cpn.set_telephone(phone)


if __name__=="__main__":
    acpn_staff=ACpnStaff("123")
    acpn_staff.setName("X-A")
    acpn_staff.setPhone("10012345678")
    print "A Staff Name:%s"%acpn_staff.getName()
    print "A Staff Phone:%s"%acpn_staff.getPhone()
    bcpn_staff=CpnStaffAdapter("456")
    bcpn_staff.setName("Y-B")
    bcpn_staff.setPhone("99987654321")
    print "B Staff Name:%s"%bcpn_staff.getName()
    print "B Staff Phone:%s"%bcpn_staff.getPhone()
~~~

## Bridge（桥接）

将抽象与实现解耦（注意此处的抽象和实现，并非抽象类和实现类的那种关系，而是一种角色的关系，这里需要好好区分一下），可以使其独立变化。


将抽象部分与它的实现部分分离，使它们都可以独立地变化。

适用性：
* 你不希望在抽象和它的实现部分之间有一个固定的绑定关系。例如这种情况可能是因，在程序运行时刻实现部分应可以被选择或者切换。
* 类的抽象以及它的实现都应该可以通过生成子类的方法加以扩充。这时Bridge 模式使可以对不同的抽象接口和实现部分进行组合，并分别对它们进行扩充。

~~~
# ConcreteImplementor 1/2
class DrawingAPI1(object):
    def draw_circle(self, x, y, radius):
        print('API1.circle at {}:{} radius {}'.format(x, y, radius))
 
 
# ConcreteImplementor 2/2
class DrawingAPI2(object):
    def draw_circle(self, x, y, radius):
        print('API2.circle at {}:{} radius {}'.format(x, y, radius))
 
 
# Refined Abstraction
class CircleShape(object):
    def __init__(self, x, y, radius, drawing_api):
        self._x = x
        self._y = y
        self._radius = radius
        self._drawing_api = drawing_api
 
    # low-level i.e. Implementation specific
    def draw(self):
        self._drawing_api.draw_circle(self._x, self._y, self._radius)
 
    # high-level i.e. Abstraction specific
    def scale(self, pct):
        self._radius *= pct
 
 
def main():
    shapes = (
        CircleShape(1, 2, 3, DrawingAPI1()),
        CircleShape(5, 7, 11, DrawingAPI2())
    )
 
    for shape in shapes:
        shape.scale(2.5)
        shape.draw()
 
 
if __name__ == '__main__':
    main()
~~~

## Composite（组合）

组合模式也叫作部分-整体模式，其定义如下：将对象组合成树形结构以表示“部分”和“整体”的层次结构，使得用户对单个对象和组合对象的使用具有一致性。

使用场景：
1. 维护部分与整体的逻辑关系，或者动态调用整体或部分的功能接口，可以考虑使用组合模式。

优点：
1. 节点增加和减少是非常自由和方便的，这也是树形结构的一大特点；
2.所有节点，不管是分支节点还是叶子结点，不管是调用一个结点，还是调用一个结点群，都是非常方便的。

缺点
1. 由于叶子结点和分支结点直接使用了实现类，而不方便使用抽象类，这大大限制了接口的影响范围；若结点接口发生变更，对系统造成的风险会比较大。

~~~
class Component:
     def __init__(self,strName):
         self.m_strName = strName
     def Add(self,com):
         pass
     def Display(self,nDepth):
         pass

 class Leaf(Component):
     def Add(self,com):
         print("leaf can't add")
     def Display(self,nDepth):
         strtemp = "-" * nDepth
         strtemp=strtemp+self.m_strName
         print(strtemp)

 class Composite(Component):
     def __init__(self,strName):
         self.m_strName = strName
         self.c = []
     def Add(self,com):
         self.c.append(com)
     def Display(self,nDepth):
         strtemp = "-"*nDepth
         strtemp=strtemp+self.m_strName
         print(strtemp)
         for com in self.c:
             com.Display(nDepth+2)

 if __name__ == "__main__":
     p = Composite("Wong")
     p.Add(Leaf("Lee"))
     p.Add(Leaf("Zhao"))
     p1 = Composite("Wu")
     p1.Add(Leaf("San"))
     p.Add(p1)
     p.Display(1)


-Wong
---Lee
---Zhao
---Wu
-----San

~~~


## Decorator（装饰）

动态地给一个对象添加一些额外的职责。在增加功能方面，装饰器模式比生成子类更为灵活。

适用性：
* 在不影响其他对象的情况下，以动态、透明的方式给单个对象添加职责。
* 处理那些可以撤消的职责。

优点：
1. 装饰器模式是继承方式的一个替代方案，可以轻量级的扩展被装饰对象的功能；
2. Python的装饰器模式是实现AOP的一种方式，便于相同操作位于不同调用位置的统一管理。

缺点

1. 多层装饰器的调试和维护有比较大的困难。

~~~
class foo(object):
    def f1(self):
        print("original f1")
 
    def f2(self):
        print("original f2")
 
 
class foo_decorator(object):
    def __init__(self, decoratee):
        self._decoratee = decoratee
 
    def f1(self):
        print("decorated f1")
        self._decoratee.f1()
 
    def __getattr__(self, name):
        return getattr(self._decoratee, name)
 
u = foo()
v = foo_decorator(u)
v.f1()
v.f2()
~~~

## Facade（外观）

外观模式也叫门面模式，要求一个子系统的外部与其内部的通信必须通过一个统一的对象进行。门面模式提供一个高层次的接口，使得子系统更易于使用。门面模式注重“统一的对象”，也就是提供一个访问子系统的接口。

使用场景：
1. 为一个复杂的子系统提供一个外界访问的接口。这类例子是生活还是蛮常见的，例如电视遥控器的抽象模型，电信运营商的用户交互设备等；
2. 需要简化操作界面时。例如常见的扁平化系统操作界面等，在生活中和工业中都很常见。

优点：
1. 减少了系统之间的相互依赖，提高了系统的灵活；
2. 提高了整体系统的安全性：封装起的系统对外的接口才可以用，隐藏了很多内部接口细节，若方法不允许使用，则在门面中可以进行灵活控制。

缺点
1. 门面模式的缺点在于，不符合开闭原则，一旦系统成形后需要修改，几乎只能重写门面代码，这比继承或者覆写等方式，或者其它一些符合开闭原则的模式风险都会大一些。


~~~
class AlarmSensor:
    def run(self):
        print "Alarm Ring..."
class WaterSprinker:
    def run(self):
        print "Spray Water..."
class EmergencyDialer:
    def run(self):
        print "Dial 119..."

class EmergencyFacade:
    def __init__(self):
        self.alarm_sensor=AlarmSensor()
        self.water_sprinker=WaterSprinker()
        self.emergency_dialer=EmergencyDialer()
    def runAll(self):
        self.alarm_sensor.run()
        self.water_sprinker.run()
        self.emergency_dialer.run()
~~~

## Flyweight（享元）

享元模式定义如下：使用共享对象支持大量细粒度对象。大量细粒度的对象的支持共享，可能会涉及这些对象的两类信息：内部状态信息和外部状态信息。内部状态信息就是可共享出来的信息，它们存储在享元对象内部，不会随着特定环境的改变而改变；外部状态信息就不可共享的信息了。享元模式中只包含内部状态信息，而不应该包含外部状态信息。

使用场景：
1. 系统中存在大量的相似对象时，可以选择享元模式提高资源利用率。咖啡订购平台比较小，若假设一个电商平台，每个买家和卖家建立起买卖关系后，买家对象和卖家对象都是占用资源的。如果一个卖家同时与多个买家建立起买卖关系呢？此时享元模式的优势就体现出来了；
2. 需要缓冲池的场景中，可以使用享元模式。如进程池，线程池等技术，就可以使用享元模式（事实上，很多的池技术中已经使得了享元模式）。

优点：
1. 减少重复对象，大大节约了系统资源。

缺点
1. 享元模式虽然节约了系统资源，但同时也提高了系统的复杂性，尤其当遇到外部状态和内部状态混在一起时，需要先将其进行分离，才可以使用享元模式。否则，会引起逻辑混乱或业务风险；
2. 享元模式中需要额外注意线程安全问题。


该模式下三个用户点了两种咖啡，最终的咖啡实例为2，而不是3
~~~
class CoffeeFactory():
    coffee_dict = {}
    def getCoffee(self, name):
        if self.coffee_dict.has_key(name) == False:
            self.coffee_dict[name] = Coffee(name)
        return self.coffee_dict[name]
    def getCoffeeCount(self):
        return len(self.coffee_dict)

class Customer:
    coffee_factory=""
    name=""
    def __init__(self,name,coffee_factory):
        self.name=name
        self.coffee_factory=coffee_factory
    def order(self,coffee_name):
        print "%s ordered a cup of coffee:%s"%(self.name,coffee_name)
        return self.coffee_factory.getCoffee(coffee_name)

if __name__=="__main__":
    coffee_factory=CoffeeFactory()
    customer_1=Customer("A Client",coffee_factory)
    customer_2=Customer("B Client",coffee_factory)
    customer_3=Customer("C Client",coffee_factory)
    c1_capp=customer_1.order("cappuccino")
    c1_capp.show()
    c2_mocha=customer_2.order("mocha")
    c2_mocha.show()
    c3_capp=customer_3.order("cappuccino")
    c3_capp.show()
    print "Num of Coffee Instance:%s"%coffee_factory.getCoffeeCount()
~~~

## Proxy（代理）
代理模式定义如下：为某对象提供一个代理，以控制对此对象的访问和控制。代理模式在使用过程中，应尽量对抽象主题类进行代理，而尽量不要对加过修饰和方法的子类代理。

应用场景：
1. 针对某特定对象进行功能和增强性扩展。如IP防火墙、远程访问代理等技术的应用；
2. 对主题对象进行保护。如大流量代理，安全代理等；
3. 减轻主题对象负载。如权限代理等。

优点:
1. 职责清晰：非常符合单一职责原则，主题对象实现真实业务逻辑，而非本职责的事务，交由代理完成；
2. 扩展性强：面对主题对象可能会有的改变，代理模式在不改变对外接口的情况下，可以实现最大程度的扩展；
3. 保证主题对象的处理逻辑：代理可以通过检查参数的方式，保证主题对象的处理逻辑输入在理想范围内。

缺点

1. 可能会降低整体业务的处理效率和速度。

~~~
import time
 
class SalesManager:
    def work(self):
        print("Sales Manager working...")
 
    def talk(self):
        print("Sales Manager ready to talk")
 
class Proxy:
    def __init__(self):
        self.busy = 'No'
        self.sales = None
 
    def work(self):
        print("Proxy checking for Sales Manager availability")
        if self.busy == 'No':
            self.sales = SalesManager()
            time.sleep(2)
            self.sales.talk()
        else:
            time.sleep(2)
            print("Sales Manager is busy")
 
 
if __name__ == '__main__':
    p = Proxy()
    p.work()
    p.busy = 'Yes'
    p.work()
~~~