#include <iostream>     // std::cout
#include <algorithm>    
#include <vector>       // std::vector

int main () {
    std::vector<int> origin {3, 5, 3, 1, 2, 3};
    std::vector<int> destination;

    // Copy elements to destination that are not 3
    std::remove_copy(origin.begin(), //first
                     origin.end(),   //last
                     std::back_inserter(destination), //d_first 
                     3);
    
    // origin is still {3, 5, 3, 1, 2, 3}
    for (auto value : origin) { 
        std::cout << value << " "; 
    }
    std::cout << std::endl;

    // destination is {5, 1, 2}
    for (auto value : destination) { 
        std::cout << value << " "; 
    }
    std::cout << std::endl;

    return 0;
}