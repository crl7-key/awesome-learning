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
    std::vector<int> v{3,2,3,9};
      // Applying the function object Display to each element of v 
    std::for_each_n(v.begin(), 2, Display()); // Will output, "3 2 "
    return 0;
}