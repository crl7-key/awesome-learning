#include <iostream>
#include <vector>
#include <algorithm>


int foo() { 
        static int i = 0; 
        return ++i; 
    }

int main()
{
    int i; 
    std::vector<int> v(10); 
  
    std::generate(v.begin(), v.end(), foo); 
  
    std::cout << "v: ";
    for (auto value : v) {
        std::cout << value << " ";
    }
    std::cout << "\n";
    // output: v :1 2 3 4 5 6 7 8 9 10 

    std::generate(v.begin(), v.end(), [n = 0] () mutable { return n++; });
 
    std::cout << "v: ";
    for (auto value: v) {
        std::cout << value << " ";
    }
    std::cout << "\n";
    // output : v: 0 1 2 3 4 5 6 7 8 9 
    return 0;
}