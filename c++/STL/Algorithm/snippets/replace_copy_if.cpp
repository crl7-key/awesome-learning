#include <iostream>     // std::cout
#include <algorithm>    
#include <vector>       // std::vector

int main () {
    auto isOdd = [](int i) {
        return ((i%2) == 1);
    };

    std::vector<int> origin {1, 2, 3, 4, 5};
    std::vector<int> destination;

    // Copy elements to destination replacing elements that return true for isOdd by 0
    std::replace_copy_if(origin.begin(),                  //first
                         origin.end(),                    //last
                         std::back_inserter(destination), //d_first 
                         isOdd,                           //condition
                         0                                //new_value
                         );
    
    // origin is still {1, 2, 3, 4, 5}
    for (auto value : origin) { 
        std::cout << value << " "; 
    }
    std::cout << std::endl;

    // destination is {0, 2, 0, 4, 0}
    for (auto value : destination) { 
        std::cout << value << " "; 
    }
    std::cout << std::endl;
    return 0;
}