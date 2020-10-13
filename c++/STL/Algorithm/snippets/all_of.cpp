#include <iostream>
#include <vector>
#include <algorithm>

int main() { 

	std::vector<int> v{10, 2, 4, 6}; 
	
	if (std::all_of(v.begin(), v.end(), [](int i){ return i % 2 == 0; })) { 
		std::cout << "All numbers are even\n"; 
	} 
    else{
        std::cout << "All numbers are not even\n"; 
    }

    // output : All numbers are even  true
    return 0;
}