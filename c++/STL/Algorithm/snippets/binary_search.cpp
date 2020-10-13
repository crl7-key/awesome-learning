#include <iostream>
#include <algorithm>
#include <vector>

void print(std::vector<int>& v) {
    for (auto p : v) {
        std::cout<< p << " ";
    }
    std::cout << std::endl;
}

int main(int argc, char const *argv[])
{
    std::vector<int> v {1, 3, 4, 5, 9};
    print(v);

    if (std::binary_search(v.begin(), v.end(), 3)) 
        std::cout << "Element found in the vector" << std::endl;
    else
        std::cout << "Element not found in the vector" << std::endl;

    auto fn = [](int a, int b){ return a > b;};

    if (std::binary_search (std::begin (v), std::end (v), 3, fn))
        std::cout << 3 << " is definitely in there - somewhere..."<< std:: endl;
    else
        std::cout << 3 << " cannot be found - maybe you got it wrong..."<< std::endl;
    return 0;
}
