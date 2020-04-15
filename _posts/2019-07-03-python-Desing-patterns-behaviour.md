---
layout: post
title:  "python设计模式-行为"
date:   2019-07-03
categories: python
tags: python
mathjax: false
---
* content
{:toc}

模式|一句话
-|-
责任链|请求的发送者和接收者之间的解耦
命令|把命令封装成对象
解释器|给定一种语言，定义它的文法表示，并定义一个解释器来解释语言中的句子。
迭代器|顺序访问集合或聚合中的元素，不在乎内部实现细节
中介者|把对象之间的交互逻辑封装成类
备忘录|在不破坏封装的前提下保存并恢复对象状态
观察者|处理对象间多对多的依赖关系，某对象改变时，所有相关对象收到通知。
状态|设计行为随状态而变得对象
策略|把一系列可互换的算法封装起来，根据用户需求选择
模板|定义算法的各个步骤，某些步骤交由子类实现
访问者|对集合的每个对象运用函数

## Chain of Responsibility（责任链）

使多个对象都有机会处理请求，从而避免了请求的发送者和接收者之间的耦合关系。将这些对象连成一条链，并沿着这条链传递该请求，直到有对象处理它为止。

应用场景：
1. 若一个请求可能由一个对请求有链式优先级的处理群所处理时，可以考虑责任链模式。

优点：
1. 将请求者与处理者分离，请求者并不知道请求是被哪个处理者所处理，易于扩展。

缺点
1. 如果责任链比较长，会有比较大的性能问题；
2. 如果责任链比较长，若业务出现问题，比较难定位是哪个处理者的问题。

~~~
class Handler:
    def successor(self, successor):
        self.successor = successor
 
class ConcreteHandler1(Handler):
    def handle(self, request):
        if request > 0 and request <= 10:
            print("in handler1")
        else:
            self.successor.handle(request)
 
class ConcreteHandler2(Handler):
    def handle(self, request):
        if request > 10 and request <= 20:
            print("in handler2")
        else:
            self.successor.handle(request)
 
class ConcreteHandler3(Handler):
    def handle(self, request):
        if request > 20 and request <= 30:
            print("in handler3")
        else:
            print('end of chain, no handler for {}'.format(request))
 
class Client:
    def __init__(self):
        h1 = ConcreteHandler1()
        h2 = ConcreteHandler2()
        h3 = ConcreteHandler3()
 
        h1.successor(h2)
        h2.successor(h3)
 
        requests = [2, 5, 14, 22, 18, 3, 35, 27, 20]
        for request in requests:
            h1.handle(request)
 
if __name__ == "__main__":
    client = Client()
~~~

## Command（命令）

将一个请求封装成一个对象，从而可以使用不同的请求将客户端参数化，对请求排队或者记录请求日志，可以提供命令的撤销和恢复功能。命令模式中通常涉及三类对象的抽象：Receiver，Command，Invoker

应用场景：
1. 触发-反馈机制的系统，都可以使用命令模式思想。如基于管道结构的命令系统（如SHELL），可以直接套用命令模式；此外，GUI系统中的操作反馈（如点击. 键入等），也可以使用命令模式思想。

优点：
1. 低耦合：调用者和接收者之间没有什么直接关系，二者通过命令中的execute接口联系；
2. 扩展性好：新命令很容易加入，也很容易拼出“组合命令”。

缺点

1. 如果业务场景中命令比较多，那么对应命令类和命令对象的数量也会增加，这样系统会膨胀得很大。

~~~
import os
 
class MoveFileCommand(object):
    def __init__(self, src, dest):
        self.src = src
        self.dest = dest
 
    def execute(self):
        self()
 
    def __call__(self):
        print('renaming {} to {}'.format(self.src, self.dest))
        os.rename(self.src, self.dest)
 
    def undo(self):
        print('renaming {} to {}'.format(self.dest, self.src))
        os.rename(self.dest, self.src)
 
 
if __name__ == "__main__":
    command_stack = []
 
    # commands are just pushed into the command stack
    command_stack.append(MoveFileCommand('foo.txt', 'bar.txt'))
    command_stack.append(MoveFileCommand('bar.txt', 'baz.txt'))
 
    # they can be executed later on
    for cmd in command_stack:
        cmd.execute()
 
    # and can also be undone at will
    for cmd in reversed(command_stack):
        cmd.undo()
~~~


## Interpreter（解释器）

给定一个语言，定义它的文法的一种表示，并定义一个解释器，这个解释器使用该表示来解释语言中的句子。

应用场景：
1. 若一个问题重复发生，可以考虑使用解释器模式。这点在数据处理和日志处理过程中使用较多，当数据的需求方需要将数据纳为己用时，必须将数据“翻译”成本系统的数据规格；同样的道理，日志分析平台也需要根据不同的日志格式翻译成统一的“语言”。
2. 特定语法解释器。如各种解释型语言的解释器，再比如自然语言中基于语法的文本分析等。

优点：
1. 在语法分析的场景中，具有比较好的扩展性。规则修改和制订比较灵活。

缺点

1. 解释规则多样化会导致解释器的爆炸；
2. 解释器目标比较单一，行为模式比较固定，因而重要的模块中尽量不要使用解释器模式。

~~~
class PlayContext():
    play_text = None

class Expression():
    def interpret(self, context):
        if len(context.play_text) == 0:
            return
        else:
            play_segs=context.play_text.split(" ")
            for play_seg in play_segs:
                pos=0
                for ele in play_seg:
                    if ele.isalpha():
                        pos+=1
                        continue
                    break
                play_chord = play_seg[0:pos]
                play_value = play_seg[pos:]
                self.execute(play_chord,play_value)
    def execute(self,play_key,play_value):
        pass

class NormGuitar(Expression):
    def execute(self, key, value):
        print "Normal Guitar Playing--Chord:%s Play Tune:%s"%(key,value)

if __name__=="__main__":
    context = PlayContext()
    context.play_text = "C53231323 Em43231323 F43231323 G63231323"
    guitar=NormGuitar()
    guitar.interpret(context)

打印如下：
Normal Guitar Playing--Chord:C Play Tune:53231323
Normal Guitar Playing--Chord:Em Play Tune:43231323
Normal Guitar Playing--Chord:F Play Tune:43231323
Normal Guitar Playing--Chord:G Play Tune:63231323
~~~

## Iterator（迭代器）

提供一种方法顺序访问一个聚合对象中各个元素, 而又不需暴露该对象的内部表示。

适用性：

访问一个聚合对象的内容而无需暴露它的内部表示。

支持对聚合对象的多种遍历。

为遍历不同的聚合结构提供一个统一的接口(即, 支持多态迭代)。


~~~
if __name__=="__main__":
    lst=["hello Alice","hello Bob","hello Eve"]
    lst_iter=iter(lst)
    print lst_iter
    print lst_iter.next()
    print lst_iter.next()
    print lst_iter.next()
    print lst_iter.next()

~~~

~~~
def MyGenerater(n):
    index=0
    while index<n:
        yield index**2
        index+=1

if __name__=="__main__":
    x_square=MyGenerater(10)
    for x in x_square:
        print x
~~~

## Mediator（中介者）

用一个中介对象封装一系列的对象交互。中介者使各对象不需要显式地互相作用，从而使其耦合松散，并可以独立地改变它们之间的交互。

应用场景：
1. 设计类图时，出现了网状结构时，可以考虑将类图设计成星型结构，这样就可以使用中介者模式了。如机场调度系统（多个跑道、飞机、指挥塔之间的调度）、路由系统；著名的MVC框架中，其中的C（Controller）就是M（Model）和V（View）的中介者。

优点：
1. 减少类与类的依赖，降低了类和类之间的耦合；
2. 容易扩展规模。

缺点
1. 中介者本身的复杂性可能会很大


有一个手机仓储管理系统，使用者有三方：销售、仓库管理员、采购。需求是：销售一旦达成订单，销售人员会通过系统的销售子系统部分通知仓储子系统，仓储子系统会将可出仓手机数量减少，同时通知采购管理子系统当前销售订单；仓储子系统的库存到达阈值以下，会通知销售子系统和采购子系统，并督促采购子系统采购；采购完成后，采购人员会把采购信息填入采购子系统，采购子系统会通知销售子系统采购完成，并通知仓库子系统增加库存。
~~~
class colleague():
    mediator = None
    def __init__(self,mediator):
        self.mediator = mediator
class purchaseColleague(colleague):
    def buyStuff(self,num):
        print "PURCHASE:Bought %s"%num
        self.mediator.execute("buy",num)
    def getNotice(self,content):
        print "PURCHASE:Get Notice--%s"%content
class warehouseColleague(colleague):
    total=0
    threshold=100
    def setThreshold(self,threshold):
        self.threshold=threshold
    def isEnough(self):
        if self.total<self.threshold:
            print "WAREHOUSE:Warning...Stock is low... "
            self.mediator.execute("warning",self.total)
            return False
        else:
            return True
    def inc(self,num):
        self.total+=num
        print "WAREHOUSE:Increase %s"%num
        self.mediator.execute("increase",num)
        self.isEnough()
    def dec(self,num):
        if num>self.total:
            print "WAREHOUSE:Error...Stock is not enough"
        else:
            self.total-=num
            print "WAREHOUSE:Decrease %s"%num
            self.mediator.execute("decrease",num)
        self.isEnough()
class salesColleague(colleague):
    def sellStuff(self,num):
        print "SALES:Sell %s"%num
        self.mediator.execute("sell",num)
    def getNotice(self, content):
        print "SALES:Get Notice--%s" % content
    

class abstractMediator():
    purchase=""
    sales=""
    warehouse=""
    def setPurchase(self,purchase):
        self.purchase=purchase
    def setWarehouse(self,warehouse):
        self.warehouse=warehouse
    def setSales(self,sales):
        self.sales=sales
    def execute(self,content,num):
        pass
class stockMediator(abstractMediator):
    def execute(self,content,num):
        print "MEDIATOR:Get Info--%s"%content
        if  content=="buy":
            self.warehouse.inc(num)
            self.sales.getNotice("Bought %s"%num)
        elif content=="increase":
            self.sales.getNotice("Inc %s"%num)
            self.purchase.getNotice("Inc %s"%num)
        elif content=="decrease":
            self.sales.getNotice("Dec %s"%num)
            self.purchase.getNotice("Dec %s"%num)
        elif content=="warning":
            self.sales.getNotice("Stock is low.%s Left."%num)
            self.purchase.getNotice("Stock is low. Please Buy More!!! %s Left"%num)
        elif content=="sell":
            self.warehouse.dec(num)
            self.purchase.getNotice("Sold %s"%num)
        else:
            pass

if  __name__=="__main__":
    mobile_mediator=stockMediator()#先配置
    mobile_purchase=purchaseColleague(mobile_mediator)
    mobile_warehouse=warehouseColleague(mobile_mediator)
    mobile_sales=salesColleague(mobile_mediator)
    mobile_mediator.setPurchase(mobile_purchase)
    mobile_mediator.setWarehouse(mobile_warehouse)
    mobile_mediator.setSales(mobile_sales)

    mobile_warehouse.setThreshold(200)
    mobile_purchase.buyStuff(300)
    mobile_sales.sellStuff(120)

打印结果如下：
PURCHASE:Bought 300
MEDIATOR:Get Info--buy
WAREHOUSE:Increase 300
MEDIATOR:Get Info--increase
SALES:Get Notice--Inc 300
PURCHASE:Get Notice--Inc 300
SALES:Get Notice--Bought 300
SALES:Sell 120
MEDIATOR:Get Info--sell
WAREHOUSE:Decrease 120
MEDIATOR:Get Info--decrease
SALES:Get Notice--Dec 120
PURCHASE:Get Notice--Dec 120
WAREHOUSE:Warning...Stock is low...
MEDIATOR:Get Info--warning
SALES:Get Notice--Stock is low.180 Left.
PURCHASE:Get Notice--Stock is low. Please Buy More!!! 180 Left
PURCHASE:Get Notice--Sold 120
~~~
## Memento（备忘录）
在不破坏封装性的前提下，捕获一个对象的内部状态，并在该对象之外保存这个状态。这样以后就可以将该对象恢复到原来保存的状态。在备忘录模式中，如果要保存的状态多，可以创造一个备忘录管理者角色来管理备忘录。

应用场景

1. 需要保存和恢复数据的相关状态场景。
2. 副本监控场景。


以模拟一个战斗角色为例。首先，创建游戏角色。GameCharacter定义了基本的生命值、攻击值、防御值以及实现角色状态控制的方法，FightCharactor实现具体的“战斗”接口。为实现保存进度的细节，还需要一个备忘录，来保存进度。
~~~
class GameCharacter():
    vitality = 0
    attack = 0
    defense = 0
    def displayState(self):
        print 'Current Values:'
        print 'Life:%d' % self.vitality
        print 'Attack:%d' % self.attack
        print 'Defence:%d' % self.defense
    def initState(self,vitality,attack,defense):
        self.vitality = vitality
        self.attack = attack
        self.defense = defense
    def saveState(self):
        return Memento(self.vitality, self.attack, self.defense)
    def recoverState(self, memento):
        self.vitality = memento.vitality
        self.attack = memento.attack
        self.defense = memento.defense
class FightCharactor(GameCharacter):
    def fight(self):
        self.vitality -= random.randint(1,10)

class Memento:
    vitality = 0
    attack = 0
    defense = 0
    def __init__(self, vitality, attack, defense):
        self.vitality = vitality
        self.attack = attack
        self.defense = defense

if __name__=="__main__":
    game_chrctr = FightCharactor()
    game_chrctr.initState(100,79,60)
    game_chrctr.displayState()
    memento = game_chrctr.saveState()
    game_chrctr.fight()
    game_chrctr.displayState()
    game_chrctr.recoverState(memento)
    game_chrctr.displayState()
~~~

##  Observer（观察者）
观察者模式也叫发布-订阅模式，其定义如下：定义对象间一种一对多的依赖关系，使得当该对象状态改变时，所有依赖于它的对象都会得到通知，并被自动更新。

应用场景：
1. 消息交换场景。如上述说到的消息队列等；
2. 多级触发场景。比如支持中断模式的场景中，一个中断即会引发一连串反应，就可以使用观察者模式。

优点：
1. 观察者与被观察者之间是抽象耦合的；
2. 可以将许多符合单一职责原则的模块进行触发，也可以很方便地实现广播。

缺点

1. 观察者模式可能会带来整体系统效率的浪费；
2. 如果被观察者之间有依赖关系，其逻辑关系的梳理需要费些心思。


火警报警器
~~~
class Observer:
    def update(self):
        pass
class AlarmSensor(Observer):
    def update(self,action):
        print "Alarm Got: %s" % action
        self.runAlarm()
    def runAlarm(self):
        print "Alarm Ring..."
class WaterSprinker(Observer):
    def update(self,action):
        print "Sprinker Got: %s" % action
        self.runSprinker()
    def runSprinker(self):
        print "Spray Water..."
class EmergencyDialer(Observer):
    def update(self,action):
        print "Dialer Got: %s"%action
        self.runDialer()
    def runDialer(self):
        print "Dial 119..."

class Observed:
    observers=[]
    action=""
    def addObserver(self,observer):
        self.observers.append(observer)
    def notifyAll(self):
        for obs in self.observers:
            obs.update(self.action)
class smokeSensor(Observed):
    def setAction(self,action):
        self.action=action
    def isFire(self):
        return True

if __name__=="__main__":
    alarm=AlarmSensor()
    sprinker=WaterSprinker()
    dialer=EmergencyDialer()

    smoke_sensor=smokeSensor()
    smoke_sensor.addObserver(alarm)
    smoke_sensor.addObserver(sprinker)
    smoke_sensor.addObserver(dialer)


    if smoke_sensor.isFire():
        smoke_sensor.setAction("On Fire!")
        smoke_sensor.notifyAll()


~~~


## State（状态）

当一个对象内在状态改变时允许其改变行为，这个对象看起来像改变了其类。

应用场景：
1. 行为状态改变的场景。这点在各种控制器中非常常见，同时，逻辑结构为状态转移图的场景中都非常适用。

优点：
1. 状态模式的优点是结构清晰，相比于if…else…简约了不少；
2. 封装性好，外部调用不必知道内部实现细节。

缺点

1. 在状态比较多时，子类也会非常多，不便于管理。


收音机AMFM切换
~~~
class State(object):
    """Base state. This is to share functionality"""
 
    def scan(self):
        """Scan the dial to the next station"""
        self.pos += 1
        if self.pos == len(self.stations):
            self.pos = 0
        print("Scanning... Station is", self.stations[self.pos], self.name)
 
 
class AmState(State):
    def __init__(self, radio):
        self.radio = radio
        self.stations = ["1250", "1380", "1510"]
        self.pos = 0
        self.name = "AM"
 
    def toggle_amfm(self):
        print("Switching to FM")
        self.radio.state = self.radio.fmstate
 
class FmState(State):
    def __init__(self, radio):
        self.radio = radio
        self.stations = ["81.3", "89.1", "103.9"]
        self.pos = 0
        self.name = "FM"
 
    def toggle_amfm(self):
        print("Switching to AM")
        self.radio.state = self.radio.amstate
 
class Radio(object):
    """A radio.     It has a scan button, and an AM/FM toggle switch."""
    def __init__(self):
        """We have an AM state and an FM state"""
        self.amstate = AmState(self)
        self.fmstate = FmState(self)
        self.state = self.amstate
 
    def toggle_amfm(self):
        self.state.toggle_amfm()
 
    def scan(self):
        self.state.scan()
 
# Test our radio out
if __name__ == '__main__':
    radio = Radio()
    actions = [radio.scan] * 2 + [radio.toggle_amfm] + [radio.scan] * 2
    actions = actions * 2
 
    for action in actions:
        action()
~~~

## Strategy（策略）

定义一组算法，将每个算法都封装起来，并使他们之间可互换。

应用场景：
1. 算法策略比较经常地需要被替换时，可以使用策略模式。

优点：
1. 各个策略可以自由切换：这也是依赖抽象类设计接口的好处之一；
2. 减少代码冗余；
3. 扩展性优秀，移植方便，使用灵活。

缺点

1. 项目比较庞大时，策略可能比较多，不便于维护；
2. 策略的使用方必须知道有哪些策略，才能决定使用哪一个策略，这与迪米特法则是相违背的。


假设某司维护着一些客户资料，需要在该司有新产品上市或者举行新活动时通知客户。现通知客户的方式有两种：短信通知、邮件通知。
~~~
class customer:
    customer_name=""
    snd_way=""
    info=""
    phone=""
    email=""
    def setPhone(self,phone):
        self.phone=phone
    def setEmail(self,mail):
        self.email=mail
    def getPhone(self):
        return self.phone
    def getEmail(self):
        return self.email
    def setInfo(self,info):
        self.info=info
    def setName(self,name):
        self.customer_name=name
    def setBrdWay(self,snd_way):
        self.snd_way=snd_way
    def sndMsg(self):
        self.snd_way.send(self.info)


class msgSender:
    dst_code=""
    def setCode(self,code):
        self.dst_code=code
    def send(self,info):
        pass
class emailSender(msgSender):
    def send(self,info):
        print "EMAIL_ADDRESS:%s EMAIL:%s"%(self.dst_code,info)
class textSender(msgSender):
    def send(self,info):
        print "TEXT_CODE:%s EMAIL:%s"%(self.dst_code,info)


if  __name__=="__main__":
    customer_x=customer()
    customer_x.setName("CUSTOMER_X")
    customer_x.setPhone("10023456789")
    customer_x.setEmail("customer_x@xmail.com")
    customer_x.setInfo("Welcome to our new party!")
    text_sender=textSender()
    text_sender.setCode(customer_x.getPhone())
    customer_x.setBrdWay(text_sender)
    customer_x.sndMsg()
    mail_sender=emailSender()
    mail_sender.setCode(customer_x.getEmail())
    customer_x.setBrdWay(mail_sender)
    customer_x.sndMsg()

打印如下：
PHONE_NUMBER:10023456789 TEXT:Welcome to our new party!
EMAIL_ADDRESS:customer_x@xmail.com EMAIL:Welcome to our new party!
~~~

## Template Method（模板方法）

定义一个操作中的算法的框架，而将一些步骤延迟到子类中，使得子类可以不改变一个算法的结构即可重新定义该算法的某些特定的步骤。子类实现的具体方法叫作基本方法，实现对基本方法高度的框架方法，叫作模板方法。

使用场景：
1. 某超类的子类中有公有的方法，并且逻辑基本相同，可以使用模板模式。必要时可以使用钩子方法约束其行为。具体如本节例子；
2. 比较复杂的算法，可以把核心算法提取出来，周边功能在子类中实现。

优点：
1. 可变的部分可以充分扩展，不变的步骤可以充分封装；
2. 提取公共代码，减少冗余代码，便于维护；
3. 具体过程可以定制，总体流程方便掌控。

缺点

1. 模板模式在抽象类中定义了子类的方法，即子类对父类产生了影响，部分影响了代码的可读性。

~~~
ingredients = "spam eggs apple"
line = '-' * 10
 
# Skeletons
def iter_elements(getter, action):    
    """Template skeleton that iterates items"""     
    for element in getter():        
        action(element)    
        print(line) 
 
def rev_elements(getter, action):
    """Template skeleton that iterates items in reverse order"""     
    for element in getter()[::-1]:        
        action(element)    
        print(line) 
 
# Getters
def get_list():    
    return ingredients.split() 
 
def get_lists():
    return [list(x) for x in ingredients.split()] 
 
# Actions
def print_item(item):    
    print(item) 
 
def reverse_item(item):
    print(item[::-1]) 
 
# Makes templates
def make_template(skeleton, getter, action):    
    """Instantiate a template method with getter and action"""    
    def template():        
        skeleton(getter, action)    
    return template 
 
# Create our template functions
templates = [make_template(s, g, a)             
             for g in (get_list, get_lists)             
             for a in (print_item, reverse_item)             
             for s in (iter_elements, rev_elements)] 
 
# Execute them
for template in templates:    
    template()
~~~


## Visitor（访问者）

封装一些作用于某种数据结构中的各元素的操作，它可以在不改变数据结构的前提下定义于作用于这些元素的新操作。


应用场景：
1. 要遍历不同的对象，根据对象进行不同的操作的场景；或者一个对象被多个不同对象顺次处理的情况，可以考虑使用访问者模式。

优点：
1. 将不同的职责非常明确地分离开来，符合单一职责原则；
2. 职责的分开也直接导致扩展非常优良，灵活性非常高，加减元素和访问者都非常容易。

缺点

1. 访问者得知了元素细节，与最小隔离原则相悖；
2. 元素变更依旧可能引起Visitor的修改。

~~~
class Node(object):
    pass
 
class A(Node):
    pass
 
class B(Node):
    pass
 
class C(A, B):
    pass
 
class Visitor(object):
    def visit(self, node, *args, **kwargs):
        meth = None
        for cls in node.__class__.__mro__:
            meth_name = 'visit_'+cls.__name__
            meth = getattr(self, meth_name, None)
            if meth:
                break
 
        if not meth:
            meth = self.generic_visit
        return meth(node, *args, **kwargs)
 
    def generic_visit(self, node, *args, **kwargs):
        print('generic_visit '+node.__class__.__name__)
 
    def visit_B(self, node, *args, **kwargs):
        print('visit_B '+node.__class__.__name__)
 
a = A()
b = B()
c = C()
visitor = Visitor()
visitor.visit(a)
visitor.visit(b)
visitor.visit(c)
~~~