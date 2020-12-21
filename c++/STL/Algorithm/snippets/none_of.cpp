#include <vector> 
#include <algorithm> 
#include <iostream> 


int main() {
    
    std::vector<int> v{1, 3, 5, 7};
	
    if (std::none_of(v.begin(), v.end(), [](int i){ return i % 2 == 0; })) { 
        std::cout << "No number is  even\n"; 
    }
    else {
        std::cout << "A number is even\n";
    }
}