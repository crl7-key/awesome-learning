#include <iostream>

int main(int argc, char const *argv[])
{
    int a = 7, b = 3;
    auto greatest = std::max(a,b);
    std::cout << greatest << std::endl;
    return 0;
}
