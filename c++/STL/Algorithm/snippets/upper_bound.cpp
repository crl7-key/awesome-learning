#include <algorithm>
#include <iostream>
#include <vector>
 
int main()
{
    std::vector<int> data = { 1, 2, 4, 5, 5, 6 };
 
    for (int i = 0; i < 7; ++i) {
        // 搜索首个大于 i 的元素
        auto upper = std::upper_bound(data.begin(), data.end(), i);
 
        std::cout << i << " < ";
        if (upper != data.end())
            std::cout << *upper << " at index " << std::distance(data.begin(), upper);
        else
            std::cout << "not found";
        std::cout << '\n';
    }
    return 0;
}