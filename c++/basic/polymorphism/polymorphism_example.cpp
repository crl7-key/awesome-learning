#include <iostream>

using namespace std;

class Base //基类
{
public:
    virtual void foo() { //虚函数实现
        cout << "Base::foo()" << endl;
    }

};

//派生类
class Derived : public Base // 必须为公有继承，否则后面调用不到，class默认为私有继承
{
public:
    virtual void foo() { // 虚函数重写实现,子类中virtual 关键字可以没有
        cout << "Derived::foo()" << endl;
    }
};

int main()
{
    Base base;       // 基类对象
    Derived derived; // 派生类对象
    
    Base* p = &base; // 父类指针指向父类对象
    p->foo();        // 调用父类的函数

    p = &derived;   // 父类指针指向子类对象，多态实现，动态绑定
    p->foo();       // 调用派生类同名函数
    return 0;
}