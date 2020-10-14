#include <iostream>     // std::cout
#include <vector>       // std::vector
#include <algorithm>    // std::copy_if

int main()
{
    auto fn = [](int i) {
        return ((i%2) == 1);
    };

    std::vector<int> vec {1, 2, 3};
    std::vector<int> res;

    // Will copy from vec [begin, end), to res
    std::copy_if(vec.begin(), vec.end(), std::back_inserter(res), fn);
    
    // res is now {1, 3}
    for (auto value : res) { 
        std::cout << value << " "; 
    }
    return 0;
}
