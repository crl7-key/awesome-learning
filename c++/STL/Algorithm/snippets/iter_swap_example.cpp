#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

template<typename T>
void print_array(T arr[],int len) {
    for(int i = 0;i < len;i++)
        std::cout << arr[i] <<" ";
    std::cout << std::endl;
}

void print_vector(const std::vector<int> &v) {
    // iterate through v and print its elements
    for(auto &elem:v) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}
 
int main()
{
    int arr[] = {10, 20, 30, 40, 50};
    std:: vector<int> vec {60, 70, 80, 90};
    std:: iter_swap(arr, vec.begin());		
    							            
    print_array(arr,sizeof(arr)/ sizeof(arr[0]));   //arr: [60] 20 30 40 50
    print_vector(vec);                              //vec: [10] 70 80 90
    return 0;
}