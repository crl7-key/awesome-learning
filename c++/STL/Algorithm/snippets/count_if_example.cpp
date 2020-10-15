#include <iostream>     // std::cout
#include <vector>       // std::vector
#include <algorithm>    // std::count_if

int main()
{
    std::vector<int> v{ 1, 2, 3, 4, 4, 3, 7, 8, 9, 10 };
 
    // use a lambda expression to count elements divisible by 3.
    int num = std::count_if(v.begin(), v.end(), [](int i){return i % 3 == 0;});
    
    std::cout << "number divisible by three: " << num << '\n';
    
   // output : number divisible by three: 3
}
