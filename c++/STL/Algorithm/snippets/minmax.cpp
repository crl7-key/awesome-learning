#include <iostream>
#include <algorithm>

int main()
{
    int a = 7, b = 3;
    
    // returns pair <3, 7>
    auto minMax1 = std::minmax(a, b);
    std::cout << "Min is " << minMax1.first <<
                 " Max is " << minMax1.second << std::endl;
    // returns pair<1,9>
    auto minMax2 = std::minmax({3, 1, 4, 1, 5, 9, 2, 6});  
    std::cout << "Min is " << minMax2.first <<
                 " Max is " << minMax2.second << std::endl;

    return 0;
}