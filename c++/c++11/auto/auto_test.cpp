#include <iostream>
#include <typeinfo>

using namespace std;

int main(int argc, char const *argv[])
{
    auto i = 10;
    std::cout << typeid(i).name() << std::endl;

    int32_t a = 1;
    int32_t& b = a;
    std::cout << typeid(b).name() << std::endl;

    auto c = b; // 此时c的类型被推导为 int32_t，而不是int32_t&
    std::cout << typeid(c).name() << std::endl;

    auto& d = b; // 此时d的类型才是int32_t&
    std::cout << typeid(d).name() << std::endl;

    const int e = 10;
    auto &f = e;// 因为auto带上&，故不去除const,f类型为const int
    // f = 10; // error非法

    int g[3] = { 1, 2, 3 };
    auto h = g;
    std::cout << typeid(h).name() << std::endl;  // output : int*

    int j[3] = { 1, 2, 3 };
    auto & k = j;
    std::cout << typeid(k).name() << std::endl; // output:: int[3]
    return 0;
}
