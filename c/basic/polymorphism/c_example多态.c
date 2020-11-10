#include <stdio.h>

//重定义一个函数指针类型
typedef void (*p)();

//基类
typedef struct _Base {
    p baseFoo;
}Base;

//派生类
typedef struct _Derived {
    p derivedFoo;
}Derived;

void baseFoo() {
    printf("%s\n","I am Base::foo()");
}

void derivedFoo(){
    printf("%s\n","I am Derived::foo()");
}

int main()
{
    Base base;          // 父类对象
    Derived derived;    // 子类对象

    base.baseFoo = baseFoo; 
    derived.derivedFoo = derivedFoo;

    Base* p = &base;    
    p->baseFoo();           // 父类调用自身方法

    p = (Base*)&derived;    // 让父类指针指向子类的对象,由于类型不匹配需要进行强制转换
    p->baseFoo();           // 调用子类方法
    return 0;
}