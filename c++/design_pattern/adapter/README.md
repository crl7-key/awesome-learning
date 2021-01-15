# C++设计模式之适配器模式

## 目录
* [什么是适配器模式？](什么是适配器模式？)
* [类适配器](#类适配器)
* [对象适配器](#对象适配器)
* [适配器模式的应用场景](#适配器模式的应用场景)
* [适配器模式优缺点](#适配器模式优缺点)
* [与其他模式的关系](#与其他模式的关系)

## 什么是适配器模式？
`Adapter Design Pattern`,顾名思义，这个模式就是用来做适配的，它**将不兼容的接口转换为可兼容的接口,让原本由于接口不兼容而不能工作的类可以一起工作**。适配器可担任两个对象间的封装器， 它会接收对于一个对象的调用， 并将其转换为另一个对象可识别的格式和接口。适配器有两种实现方式：类适配器和对象适配器。

## 类适配器
[类适配器](adaptor.cpp)使用继承关系来实现。
```cpp
// 类适配器：基于继承
class Target { // 客户期望的接口，可以使具体或抽象的类，也可以是接口
public:
    virtual void foo1() {
        std::cout << "Target::foo1()" << std::endl;
    }

    virtual void foo2() {
        std::cout << "Target::foo2()" << std::endl;
    }

    virtual void fooc() {
        std::cout << "Target::fooc()" << std::endl;
    }
    virtual ~Target(){}
};

class Adaptee { // 需要适配的类
public:
    Adaptee() {
        std::cout << "Adaptee()" << std::endl;
    }

    void fooa() {
        std::cout << "Adaptee::fooa()" << std::endl;
    }

    void foob() {
        std::cout << "Adaptee::foob()" << std::endl;
    }
    
    void fooc() {
        std::cout << "Adaptee::fooc()" << std::endl;
    }
};

class Adaptor : public Adaptee ,public Target {
public:
     Adaptor(Adaptee* adaptee,Target* target) : m_adaptee(adaptee),m_target(target) {     
    }
    void foo1() {
        m_adaptee->fooa();
    }

    void foo2() {
        // 重新实现foo2
    }

    void fooc() {
        m_adaptee->fooc();
        m_target->fooc();
    }
    
private:
    Adaptee* m_adaptee;
    Target* m_target;
};
```

## 对象适配器
[对象适配器](adapter.cpp)使用组合关系来实现。
```cpp
// 对象适配器：自由组合
class Target { // 客户期望的接口，可以使具体或抽象的类，也可以是接口
public:
    virtual void foo1() {
        std::cout << "Target::foo1()" << std::endl;
    }

    virtual void foo2() {
        std::cout << "Target::foo2()" << std::endl;
    }

    virtual void fooc() {
        std::cout << "Target::fooc()" << std::endl;
    }
    virtual ~Target(){}
};

class Adaptee { // 需要适配的类
public:
    Adaptee() {
        std::cout << "Adaptee()" << std::endl;
    }

    void fooa() {
        std::cout << "Adaptee::fooa()" << std::endl;
    }

    void foob() {
        std::cout << "Adaptee::foob()" << std::endl;
    }
    
    void fooc() {
        std::cout << "Adaptee::fooc()" << std::endl;
    }
};


class Adaptor : public Target { // 将需要适配的类转换成一组符合targe接口定义的接口
public:
    Adaptor(Adaptee* adaptee) : m_adaptee(adaptee) {     
    }

    void foo1() {
        m_adaptee->fooa();
    }

    void foo2() {
        // 重新实现 foo2
    }

    void fooc() {
        m_adaptee->fooc();
    }
private:
    Adaptee* m_adaptee;
};
```

针对实际的开发中，选择哪种实现方式判断的标准主要有两个，一个是`Adaptee`（需要适配的）接口的个数，另一个是`Adaptee`和`Target`的契合程度。

- 如果`Adaptee`接口并不多，那两种实现方式都可以。

- 如果`Adaptee`接口很多，而且`Adaptee`和`Target`接口定义大部分相同，推荐使用类适配器，因为`Adaptor`复用父类`Adaptee`的接口，比起对象适配器的实现方式，`Adaptor`的代码量要少一些。

- 如果`Adaptee`接口很多，而且`Adaptee`和`Target`接口定义大部分不相同，推荐使用对象适配器，因为组合结构相对于继承更加灵活。


## 适配器模式的应用场景
- 封装有缺陷的接口设计

- 统一多个类的接口设计

- 替换依赖的外部系统

- 兼容老版本接口

- 适配不同格式的数据

## 适配器模式优缺点
**优点**：
- 单一职责原则，可以将接口或数据转换代码从程序主要业务逻辑中分离

- 开闭原则。通过`Target`接口与适配器进行交互，能在不修改现有`Target`代码的情况下在程序中添加新类型的适配器

**缺点**：
- 代码整体复杂度增加，因为需要新增一系列接口和类。


## 与其它模式的关系

- 桥接模式 ：通常会于开发前期进行设计，目的是将接口部分和实现部分分离，从而让它们可以较为容易、也相对独立地加以改变， 使你能够将程序的各个部分独立开来以便开发。 另一方面， 适配器模式通常在已有程序中使用， 让相互不兼容的类能很好地合作。

- 外观模式：外观模式为现有对象定义了一个新接口， 适配器则会试图运用已有的接口。 适配器通常只封装一个对象， 外观通常会作用于整个对象子系统上。

- 代理模式：代理模式在不改变原始类接口的条件下，为原始类定义一个代理类，主要目的是控制访问，而非加强功能，这是它跟装饰器模式最大的不同，适配器能为被封装对象提供不同的接口， 代理模式能为对象提供相同的接口， 装饰则能为对象提供加强的接口。

- 装饰者模式：装饰者模式在不改变原始类接口的情况下，对原始类功能进行增强，并且支持多个装饰器的嵌套使用。适配器可以对已有对象的接口进行修改， 装饰模式则能在不改变对象接口的前提下强化对象功能。 此外， 装饰还支持递归组合， 适配器则无法实现。


- 桥接、 状态模式和策略模式 （在某种程度上包括适配器） 模式的接口非常相似。 实际上， 它们都基于组合模式——即将工作委派给其他对象， 不过也各自解决了不同的问题。 模式并不只是以特定方式组织代码的配方， 你还可以使用它们来和其他开发者讨论模式所解决的问题。
