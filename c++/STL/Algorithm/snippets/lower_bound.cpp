#include <algorithm>
#include <iostream>
#include <vector>
 
int main()
{
    std::vector<int> data = {3, -1, 2, 5, 10, 6, 7, 4};
    std::sort(data.begin(), data.end());
    
    auto lower = std::lower_bound(data.begin(),data.end(),8);
    
    std::cout << "The lower bound element is " << *lower << std::endl;
    return 0;
}