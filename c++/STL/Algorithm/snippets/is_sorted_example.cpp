#include <iostream>
#include <algorithm>
#include <iterator>

int main()
{
    int digits[] = {3, 1, 4, 1, 5};
 
    for (auto i : digits) std::cout << i << ' ';
    std::cout << ": is_sorted: " << std::boolalpha
              << std::is_sorted(std::begin(digits), std::end(digits)) << '\n';
              // output : 3 1 4 1 5 : is_sorted: false
    std::sort(std::begin(digits), std::end(digits));
 
    for (auto i : digits) std::cout << i << ' ';
    std::cout << ": is_sorted: "
              << std::is_sorted(std::begin(digits), std::end(digits)) << '\n';

              // output : 1 1 3 4 5 : is_sorted: true
    return 0;
}