#include <iostream>     // std::cout
#include <vector>       // std::vector
#include <algorithm>    // std::adjacent_find
#include <functional>   // std::greater

bool myOp(int x, int y) {
    return x > y;
}

int main()
{
    std::vector<int> v{ 1, 2, 3, 3, 4, 3, 7, 8, 9, 10 };
    auto i  = std::adjacent_find(v.begin(), v.end());  // 搜索 v[first, last) 中两个连续的相等元素的第一个元素。

    std::cout << "The first pair of repeated elements are: " << *i <<'\n';

    // ouput :  The first pair of repeated elements are: 3
 
    auto i2 = std::adjacent_find(v.begin(), v.end(), std::greater<int>());
    if (i2 == v.end()) {
         std::cout << "The entire vector is sorted in ascending order\n";
     } else {
         std::cout << "The last element in the non-decreasing subsequence is at: "
                   << std::distance(v.begin(), i2) << '\n';
     }
    // output : The last element in the non-decreasing subsequence is at: 4 
    
    auto i3 = std::adjacent_find(v.begin(), v.end(), myOp);
    if (i3 == v.end()) {
        std::cout << "The entire vector is sorted in ascending order\n";
    } else {
        std::cout << "The last element in the non-decreasing subsequence is at: "
                  << std::distance(v.begin(), i3) << '\n';
    }
   // output : The last element in the non-decreasing subsequence is at: 4
    return 0;
}
