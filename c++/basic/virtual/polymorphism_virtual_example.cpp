#include <iostream>

using namespace std;

class Base // 基类
{
public:
    virtual void foo() { //虚函数实现
        cout << "Base::foo()" << endl;
    }

};

// 派生类1
class Derived1 : public Base // 必须为公有继承，否则后面调用不到，class默认为私有继承
{
public:
    virtual void foo() { // 虚函数重写实现,子类中virtual 关键字可以没有
        cout << "Derived1::foo()" << endl;
    }
};

// 派生类2
class Derived2 : public Base // 必须为公有继承，否则后面调用不到，class默认为私有继承
{
public:
    virtual void foo() {    // 虚函数重写实现,子类中virtual 关键字可以没有
        cout << "Derived2::foo()" << endl;
    }
};

void globalFoo(Base* arr[],int n) {
    for(int i = 0; i < n ; ++i) {
        arr[i]->foo();
    }
}

int main()
{
    Base* arr[] = {new Derived1,new Derived2};

    globalFoo(arr,2);

    return 0;
}