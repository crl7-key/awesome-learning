# C++设计模式之原型模式
![](https://img.shields.io/badge/standard--readme-MIT-green?style=flat&logo=appveyor)  


## 目录

## 原型模式
 原型模式是一种创建型设计模式,用于创建重复的对象,它提供了一种创建相同对象的最佳方式。当直接创建对象需要较大的代价时，可以使用原型模式。例如对象需要读取文件或者向服务器发起请求获取某些必要数据才可以被创建,每次都直接创建显然有很大代价,所以可以考虑缓存数据,**提供一个克隆接口**,直接用缓存的数据创建对象。

原型模式的实现较为简单,**基类提供Clone纯虚函数,子类只需要实现这个Clone函数即可**。
```c++
#include <iostream>

class Prototype {
public:
    Prototype() {}
    virtual ~Prototype() {}
    
    virtual Prototype* Clone() = 0;

    virtual void Show() = 0;
};

class ConcretePrototype: public Prototype {
public:
    Prototype* Clone() override {
        return new ConcretePrototype();
    }

    void Show() override {
        std::cout << "ConcretePrototype::Show()" << std::endl;
    }
};

int main(int argc, char const *argv[])  
{
    Prototype* prototype = new ConcretePrototype();
    prototype->Show();

    Prototype* prototype_bak = prototype1->Clone();
    prototype_bak->Show();

    return 0;
}
```
Prototype的意义: 当一个基类指向某个子类对象时,这时如果想要拷贝这个子类对象是比较困难的,因为只通过一个基类指针我们不知道该指针究竟指向了什么类型的对象(有很多派生类),即无法调用相应的构造函数,通过`typeid`加`switch`貌似代价太大,这个时候就可以使用原型模式。

**[⬆ 返回顶部](#目录)**