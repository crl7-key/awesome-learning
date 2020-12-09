#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::cout << "Max heap:" << std::endl;
 
    std::vector<int> data =  { 3, 2, 4, 1, 5, 9 };
    
    std::make_heap(data.begin(),data.end());
    
    std::cout << "The maximum element of heap is : "; 
    std::cout << data.front() << std::endl;  // output : 9
    
    // print heap
    for(int i = 0; i < data.size(); ++i) {
        std::cout << data[i] << " " ;
    }
    return 0;
}