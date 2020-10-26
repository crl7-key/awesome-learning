#include <iostream>

using namespace std;

// 虚函数是动态绑定的,默认参数是静态绑定的。默认参数的使用需要看指针或者应用本身的类型，而不是对象的类型
class Base 
{ 
public: 
    virtual void foo (int i = 10) { 
        cout << "Base::fun(), i = " << i << endl; 
    } 
}; 

class Derived : public Base 
{ 
public: 
    virtual void foo (int i = 20) { 
        cout << "Derived::fun(), i = " << i << endl; 
    } 
}; 

int main(int argc, char const *argv[])
{
    Derived obj;    // 派生类对象

    Base* p = &obj; // 基类指针指向派生类对象

    p->foo();      // 调用派生类同名函数 output: 20

    return 0;
}
