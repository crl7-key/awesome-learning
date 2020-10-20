#include <iostream>   // std::cout
#include <vector>     // std::vector
#include <algorithm>  // std::fill_n

int main()
{
    std::vector<int> v{ 1, 2, 3, 4, 4, 3, 7, 8, 9, 10 };

    int searchme = 4;
    if(std::find(std::begin(v), std::end(v), searchme) != std::end(v)){
        std::cout <<"\n v contains 4";
    }
    else
        std::cout<<"No match !!";
    return 0;
}