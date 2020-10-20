#include <iostream>
#include <vector>
#include <algorithm>

void print_vector(const std::vector<int> &v) {
    // iterate through v and print its elements
    for(auto &elem:v) {
        std::cout << elem << " ";
    }
    std::cout<<std::endl;
}

int main()
{
    std::vector<int> v = {1,1,1,1,1,1,1,1};

    std::cout << "Before fill_n: ";
    print_vector(v);
    // output : Before fill_n: 1 1 1 1 1 1 1 1 
    

    // set the first half of v's elements to zero
    std::fill_n(v.begin(), v.size()/2, 0);

    std::cout << "After  fill_n: ";
    print_vector(v);
    //output : After  fill_n: 0 0 0 0 1 1 1 1 
    return 0;
}