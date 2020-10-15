#include <iostream>     // std::cout
#include <vector>       // std::vector
#include <algorithm>    // std::count



int main()
{
    
    std::vector<int> v{ 1, 2, 3, 4, 4, 3, 7, 8, 9, 10 };
    int target  = 3;
    int num = std::count(v.begin(), v.end(), target);
    
    std::cout << "number: " << target << " count: " << num << '\n';
    return 0;
}
