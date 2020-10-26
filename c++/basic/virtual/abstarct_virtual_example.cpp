#include <iostream>

using namespace std;

class Abstract {
public: 
    virtual void foo() = 0; // 纯虚函数

    virtual ~Abstract() = 0;    // 纯虚析构
};

Abstract::~Abstract() {
    cout << "Abstract::~Abstract()" << endl;
}

class Derived : public Abstract
{
public:
    void foo() {    // 实现了抽象类的纯虚函数
        cout << "Derived::foo()" << endl;
    }
};

int main(int argc, char const *argv[])
{
    /*
     * 1. 抽象类只能作为基类来派生新类使用
     * 2. 抽象类的指针和引用指向由抽象类派生出来的类的对象
     */

    //Abstract obj; // error 抽象类，不实例化

    Abstract* obj; // ok 可以定义抽象类的指针

    //Abstract* obj2 = new Abstract(); // error 抽象类，不能创建对象

    Abstract* p = new Derived(); // ok 抽象类的指针和引用 -> 由抽象类派生出来的类的对象
    p->foo();


    return 0;
}
