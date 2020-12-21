#include <iostream>     // std::cout
#include <algorithm>    
#include <vector>       // std::vector

int main () {
    std::vector<int> origin {3, 5, 3, 1, 2, 3};

    // replaces 3 by 0
    std::replace(origin.begin(), //first
                 origin.end(),   //last
                 3,              //old_vale 
                 0               //new_value 
                 );
    
    // origin is now {0, 5, 0, 1, 2, 0}
    for (auto value : origin) { 
        std::cout << value << " "; 
    }
    return 0;
}
