#include <iostream>
#include <algorithm>
#include <vector>
 
int main()
{
    std::vector<int> v { 3, 1, 4, 1, 5, 9 };
 
    std::cout << "initially, v: ";
    for (auto i : v) std::cout << i << ' ';
    std::cout << '\n';
    // output : initially, v: 3 1 4 1 5 9 

    if (!std::is_heap(v.begin(), v.end())) {
        std::cout << "making heap...\n";
        std::make_heap(v.begin(), v.end());
    }
 
    std::cout << "after make_heap, v: ";
    for (auto i : v) std::cout << i << ' ';
    std::cout << '\n';
    // after make_heap, v: 9 5 4 1 1 3
    return 0;
}