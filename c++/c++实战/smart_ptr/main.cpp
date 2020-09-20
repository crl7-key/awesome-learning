#include "shared_ptr.h"
#include "shape.h"


int main()
{
    shared_ptr<circle> ptr1(new circle());
    std::cout << "use count of ptr1 is " << ptr1.use_count() << std::endl;
    shared_ptr<shape> ptr2, ptr3;
    std::cout << "use count of ptr2 was " << ptr2.use_count() << std::endl;
    ptr2 = ptr1;

    std::cout << "now three shared_ptr to the same resource" << std::endl;

    std::cout << "use count of ptr1 is now " << ptr1.use_count() << std::endl;

    std::cout << "use count of ptr2 is now " << ptr2.use_count() << std::endl;

    std::cout << "use count of ptr3 is now " << ptr3.use_count() << std::endl;

    if (ptr1) {
        std::cout << "ptr1 is not empty()" << std::endl;
    }

    // 会先调用赋值函数,由编译器决定调用的是拷贝构造还是移动构造,造出一个新的临时对象出来,临时对象会在跳出作用域后被析构掉。
    // 在析构函数中,会先判断该临时对象的是否指向资源,如果没有,析构结束。否则,对引用计数减1,判断引用计数是否为0,如果为0,删除共享引用计数指针,否则不操作。
    std::cout << "此时2个shared_ptr指向同一个资源" << std::endl;
    ptr2 = std::move(ptr1);
    if (!ptr1 && ptr2) { // 调用bool重载运算符
        std::cout << "ptr1 move to ptr2" << std::endl;
        std::cout << "use count of ptr1 is now " << ptr1.use_count() << std::endl;
        std::cout << "use count of ptr2 is now " << ptr2.use_count() << std::endl;
        std::cout << "use count of ptr3 is now " << ptr3.use_count() << std::endl;
    }
    return 0;
}

