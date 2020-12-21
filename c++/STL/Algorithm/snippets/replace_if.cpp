#include <iostream>     // std::cout
#include <algorithm>    
#include <vector>       // std::vector

int main () {
    auto isOdd = [](int i) {
        return ((i%2) == 1);
    };

    std::vector<int> origin {1, 2, 3, 4, 5};

    // replaces values for which isOdd returns true by 0
    std::replace_if(origin.begin(), //first
                 origin.end(),   //last
                 isOdd,          //condition 
                 0               //new_value 
                 );
    
    // origin is now {0, 2, 0, 4, 0}
    for (auto value : origin) { 
        std::cout << value << " "; 
    }
    return 0;
}