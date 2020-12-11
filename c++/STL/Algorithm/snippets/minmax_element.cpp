#include <iostream>
#include <algorithm>
#include <array>

int main()
{
    std::array<int,7> foo {3,7,2,9,5,8,6};  // 3,7,2,9,5,8,6

    //  在[first，last）范围内的最小值作为第一个元素，而最大值作为第二个元素
    auto result = std::minmax_element (foo.begin(),foo.end());

    std::cout << "min is " << *result.first; 
    std::cout << ", at position " << (result.first-foo.begin()) << std::endl;
    std::cout << "max is " << *result.second;
    std::cout << ", at position " << (result.second-foo.begin()) << std::endl;
    
    return 0;
}