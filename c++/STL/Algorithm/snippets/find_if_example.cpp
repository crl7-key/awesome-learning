#include <iostream>
#include <algorithm>
#include <vector>

bool IsOdd (int i) {
    return ((i%2)==1);
}

int main()
{
    std::vector<int> v{ 1, 2, 3, 4, 4, 3, 7, 8, 9, 10 };
    if(std::find_if(std::begin(v), std::end(v), IsOdd) != std::end(v)) {
        std::cout <<"\n Odd Value Found";
    }
    else
        std::cout<<"No match !!";
    // output: OddValue Found
    return 0;
}