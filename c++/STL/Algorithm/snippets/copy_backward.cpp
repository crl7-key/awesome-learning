#include <iostream>     // std::cout
#include <vector>       // std::vector
#include <algorithm>    // std::copy_backward

int main()
{
    std::vector<int> vec;
    for (int i = 0; i < 10; i++) {
        vec.push_back(i);
    }
    std::vector<int> res(15);

    std::copy_backward(vec.begin(), vec.end(), res.end());
    
    std::cout << "res contains: ";
    for (auto value : res) {  
        std::cout << value << " "; 
     }
    return 0;
}
