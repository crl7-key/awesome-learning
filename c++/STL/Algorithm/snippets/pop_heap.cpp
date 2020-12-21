#include <algorithm> 
#include <iostream> 
#include <vector>

int main() {
    
    std::vector<int> v = {2,5,8,7,4,5};
    
    //converting vector into heap
    make_heap(v.begin(),v.end());
    //printing first element
    std::cout << "first element of the heap: " << v.front() << std::endl;
    //outputs 8
    
    for(auto n : v)
        std::cout << n << ' ';
    std::cout << '\n';
    
    pop_heap(v.begin(),v.end());
    //pops the maximum element in the heap
    //printing frist element
    std::cout << "first element of the heap after using pop_heap: " << v.front() << std::endl;
    
    for(auto n : v)
        std::cout << n << ' ';
    std::cout << '\n';
    
    return 0;
} 