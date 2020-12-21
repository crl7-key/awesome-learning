#include <algorithm> 
#include <iostream> 

int main() {
    
    // Creating array of size 8
    int v[] = { 3, 2, 10, 45, 33, 56, 23, 47 }, i; 
  
    // Using std::nth_element with n as 5 
    std::nth_element(v, v + 4, v + 8); 
  
    // Since, n is 5 so 5th element should be sorted 
    for (i = 0; i < 8; ++i) { 
        std::cout << v[i] << " "; 
    } 
    std::cout << std::endl;
    
    std::cout << "The median is " << v[(sizeof(v)/sizeof(v[0]))/2] << '\n';
    
    return 0;
} 