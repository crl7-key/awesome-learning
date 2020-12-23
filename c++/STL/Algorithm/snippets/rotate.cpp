#include <vector>
#include <iostream>
#include <algorithm>
 
int main()
{
    std::vector<int> v{2, 4, 2, 0, 5, 10, 7, 3, 7, 1}; 
 
    std::cout << "before sort:      ";
    for (int n: v)
        std::cout << n << ' ';
    std::cout << '\n';
 
    // 插入排序
    for (auto i = v.begin(); i != v.end(); ++i) {
        std::rotate(std::upper_bound(v.begin(), i, *i), i, i+1);
    }
 
    std::cout << "after sort:       ";
    for (int n: v)
        std::cout << n << ' ';
    std::cout << '\n';
 
    // 简单地旋转到左侧
    std::rotate(v.begin(), v.begin() + 1, v.end());
 
    std::cout << "simple rotate left  : ";
    for (int n: v)
        std::cout << n << ' ';
    std::cout << '\n';
 
    // 简单地旋转到右侧
    std::rotate(v.rbegin(), v.rbegin() + 1, v.rend());
 
    std::cout << "simple rotate right : ";
    for (int n: v)
        std::cout << n << ' ';
    std::cout << '\n';
 
}