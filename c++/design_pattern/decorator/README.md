# C++设计模式之装饰器模式


## 装饰器模式？

允许向一个现有的对象添加新的功能(动态的扩展类的功能),同时又不改变其结构。这种类型的设计模式属于结构型模式。主要用于在不增加子类的情况下增强一个类的功能。遵循了对修改关闭和对扩展开放的原则。

它的主要作用就是：
- 增强一个类原有的功能
- 为一个类添加新的功能
- 装饰器模式也不会改变原有的类


假如有一个组件基类，派生出`产品1`和`产品2`，一个产品只有一个功能，但是如果一个`产品3`需要同时拥有这两个产品的功能：
```c++
// 抽象组件
class Component {
public:
    virtual ~Component() {}

    virtual void Configuration() = 0;
};

class Product1 : public Component {
public:
    void Configuration() override {
        std::cout << "Product1:: Configuration() " << std::endl;
    }
};

class Product2 : public Component {
public:
    void Configuration() override {
        std::cout << "Product2:: Configuration() " << std::endl;
    }
};

class Product3 : public Component {
public:
    void Configuration() override {
        std::cout << "Product1:: Configuration() " << std::endl;
        std::cout << "Product2:: Configuration() " << std::endl;
    }
};

int main(int argc, char const *argv[])
{
    Component* component = new Product3();
    component->Configuration();
    return 0;
}
```
假设如果有一个产品需要拥有很多功能,那还需要扩展出很多子类,显然不太灵活,这就用到了装饰器模式，装饰器模式可以增强现有类的功能，可以看如下代码实现：
```c++
class Component {
public:
  virtual ~Component() {}

  virtual void Configuration() = 0;
};

class Product1Decorator : public Component {
public:
    Product1Decorator() {}
    Product1Decorator(Component* component) { m_component = component; }
    void Configuration() override {
        std::cout << "Product1Decorator::Configuration()" << std::endl;
        if (m_component) m_component->Configuration();
    }

private:
    Component* m_component;
};

class Product2Decorator : public Component {
public:
    Product2Decorator() {}
    Product2Decorator(Component* component) { m_component = component; }
    void Configuration() override {
        std::cout << "Product2Decorator::Configuration()" << std::endl;
        if (m_component) m_component->Configuration();
    }

  private:
  Component* m_component;
};

int main() {
  Component* component = new Product1Decorator();
  component = new Product2Decorator(component); // 暂时忽略内存泄漏
  component->Configuration();
  return 0;
}
```

这里装饰器类和原始类继承同样的父类，这样就可以对原始类嵌套多个装饰器类，起到增强类功能的作用。

装饰器模式和代理模式有个重要区别就是装饰器模式是对一个类的增强，附加的是跟原始类有关的功能，而代理模式附加的是与原始类无关的额外功能。

当我们需要扩展一个类的功能或者需要动态增加功能时，可以考虑使用装饰器模式。