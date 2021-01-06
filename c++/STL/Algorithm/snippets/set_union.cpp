#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>


int main()
{
    std::vector<int> v1 {1,2,3,4,5,6,7,8};
    std::vector<int> v2 {        5,  7,  9,10};

    // the destination needs to fit all merged values, we'll prune the extra elements later
    std::vector<int> destination(v1.size() + v2.size());

    // set_union requires sorted ranges
    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());

    // returns iterator to the end of the constructed range
    auto it = std::set_union(v1.begin(), v1.end(),  // first range 
                             v2.begin(), v2.end(),  // second range
                             destination.begin());

    // prune extra values
    destination.resize(it - destination.begin()); 

    // destination is now {1, 2, 3, 4, 5, 6 , 7, 8 ,9 , 10}
    for (auto value : destination) { 
        std::cout << value << " "; 
    }
    return 0;
}