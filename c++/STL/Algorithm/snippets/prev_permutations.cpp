#include <algorithm> 
#include <iostream> 

int main() {
    
    int arr[] = {1,2,3};

    std::sort (arr,arr+3);
    std::reverse (arr,arr+3);

    std::cout << "The 3! possible permutations with 3 elements:\n";
    do {
      std::cout << arr[0] << ' ' << arr[1] << ' ' << arr[2] << '\n';
    } while ( std::prev_permutation(arr,arr+3) );

    std::cout << "After loop: " << arr[0] << ' ' << arr[1] << ' ' << arr[2] << '\n';

    return 0;
} 