#include <iostream>


void testPtr(int *ptr) {
    int a = 12;
    ptr = &a;
    std::cout << " " << *ptr << std::endl;
    std::cout << "the address after assignmentis " << ptr << std::endl;
}

void testRefer(int &ref) {
    int a = 12;
    ref = a;
    std::cout << sizeof(ref) << std::endl; // output : 4 ，sizeof引用得到的是引用所指向变量的大小
}

int main(int argc, char const *argv[])
{
    int *ptr = NULL; // 指针可以为 null
    std::cout << "the address before initialization is " << ptr  << std::endl; 
    testPtr(ptr);
    if(ptr == NULL) {
        std::cout << "pointer ptr is NULL" << std::endl;// 当把指针作为参数进行传递时，也是将实参的一个拷贝传递给形参，两者指向的地址相同，但不是同一个变量
    }

    int a = 10;
    int *b = &a;
    testPtr(b); // 改变指针指向，但是没改变指针的所指的内容
    std::cout << a << std::endl;  // output: 10
    std::cout << sizeof(b) << std::endl; // output: 8 ， sizeof指针得到的是本指针的大小
    std::cout << *b << std::endl; // output: 10

    a = 10;
    testRefer(a);
    std::cout << a << std::endl; // output: 12
    return 0;
}
