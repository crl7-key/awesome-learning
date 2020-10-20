#include <iostream>
#include <vector>
#include <algorithm>

class Display {
public: 
    void operator() (int i) { 
    std::cout << i << " ";
    }
};

int main()
{
    std::vector<int> a{3,2,3,9};
      // Applying the function object Display to each element of a 
    std::for_each(a.begin(), a.end(), Display()); // Will output: 3 2 3 9
    return 0;
}