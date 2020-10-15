#include <iostream>
#include <algorithm>
#include <vector>

int main(int argc, char const *argv[])
{
    std::vector<int> vec {1, 2, 3};
    std::vector<int> res;
 
    std::copy(vec.begin(), vec.end(), std::back_inserter(res));
 
    for (auto n : res)
        std::cout << n << ' ';
 
    std::cout << '\n';
    // output : res is now {1, 2, 3}
    return 0;
}
