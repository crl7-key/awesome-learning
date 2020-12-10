#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<int> v1 {8, 2, 0, 4};
    std::vector<int> v2 {7, 3, 5};
    
    std::vector<int> destination(v1.size() + v2.size());

    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());

    std::merge(v1.begin(), v1.end(), // first range 
               v2.begin(), v2.end(), // second range
               destination.begin());

    for (auto value : destination) { 
        std::cout << value << " ";  // output : 0, 2, 3, 4, 5, 7, 8
    }
    
    return 0;
}