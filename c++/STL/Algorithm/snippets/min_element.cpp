#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<int> vec = {3, -1, 2, 10, 4};

    auto smallestIt = std::min_element(vec.begin(), vec.end()); 
   
    std::cout << "The smallest element is " << *smallestIt << std::endl; // outpu: -1
    return 0;
}