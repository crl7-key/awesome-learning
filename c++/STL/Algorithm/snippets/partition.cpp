#include <algorithm> 
#include <iostream> 
#include <vector>

int main() {
    
    std::vector<int> my_vector = { 2, 1, 5, 6, 8, 7 };

    // Partitioning my_vector in basis of even numbers condition
    std::partition(my_vector.begin(), my_vector.end(), [](int x){ 
        return x%2==0; 
    });
    
    // Verifying if my_vector is partitioned
    if ( std::is_partitioned(my_vector.begin(), my_vector.end(), [](int x){ return x%2==0; } )) {
        std::cout << "The vector is partitioned!\n" << std::endl;
    } else{
        std::cout << "The vector is not partitioned!\n" << std::endl;
    }
    
    // output: 2 8 6 5 1 7
    for (auto n : my_vector)
        std::cout << n << ' ';
    std::cout << '\n'; 
    
    return 0;
} 