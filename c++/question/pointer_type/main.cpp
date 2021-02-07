#include <iostream>

#include <typeinfo>


int main(int argc, char const *argv[])
{
    int *p1[10]; // 指针数组

    std::cout << "p1的类型是 " << typeid(p1).name() << std::endl; // output: A10_Pi

    int (*p2)[10]; // 数组指针

    std::cout << "p2的类型是 " << typeid(p2).name() << std::endl; // output: PA10_i

    int *p3(int); // 函数声明，函数名为p3,参数是int类型，返回值是int* 类型

    std::cout << "p3的类型是 " << typeid(p3).name() << std::endl; //output: FPiiE
    int (*p4)(int); // 函数指针,强调的是指针,该指针指向的函数具有int类型参数，返回值类型是int类型

    std::cout << "p4的类型是 " << typeid(p4).name() << std::endl; //output: PFiiE
    return 0;
}
