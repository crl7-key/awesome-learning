#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    int a = 7, b = 3;
    auto smallest = std::min(a, b);
    
    std::cout << smallest << " "; // output : 3
    return 0;
}