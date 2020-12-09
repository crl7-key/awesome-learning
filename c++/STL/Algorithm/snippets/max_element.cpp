#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> data = {3, -1, 2, 10, 4};

    auto greatestIt = std::max_element(data.begin(), data.end()); 
    
    std::cout << "The greatest element is " << *greatestIt << std::endl; // output: 10
    return 0;
}