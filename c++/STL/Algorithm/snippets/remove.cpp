#include <iostream>     // std::cout
#include <algorithm>    
#include <vector>       // std::vector

int main () {
    std::vector<int> v {3, 5, 3, 1, 2, 3};

    // removes all elements that are 3
    auto newEndIt = std::remove(v.begin(), v.end(), 3);
    
    // Erase elements from [newEndIt, v.end()]
    v.erase(newEndIt, v.end());

    // v is now {5, 1, 2}
    for (auto value : v) { 
        std::cout << value << " "; 
    }

    return 0;
}
