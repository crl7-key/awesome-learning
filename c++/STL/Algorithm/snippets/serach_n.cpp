#include<iostream>
#include<vector>
#include<algorithm>

int main() {
    // Sequence to search in
    std::vector<int> vec = { 7, 6, 0, 4, 4, 9, 3, 4, 8 }; 
  
    // Value to be searched for 
    int v1 = 4;

    // Number of successive elements
    int v2 = 2;

    // Iterator for storing the returning pointer 
    std::vector<int>::iterator it; 

    it = std::search_n(vec.begin(), vec.end(), v2, v1); 
  
    // checking if iterator i1 contains end pointer of v1 or not 
    if (it != vec.end()) { 
        std::cout << "v1 is present consecutively 2 times at index "
             << (it - vec.begin()); 
    } else { 
        std::cout << "v1 is not present consecutively 2 times in "
             << "vector vec"; 
    }
    return 0;
}