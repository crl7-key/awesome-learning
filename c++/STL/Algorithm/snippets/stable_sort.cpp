#include <iostream>
#include <algorithm>


int main(int argc, const char** argv) 
{
    //sample array
    int arr[] = {1,1,3,5,4,9,4};
    //sorting the array
    std::stable_sort(arr,arr + 7);
    //array after sorting
    for(int i = 0;i < 7;i++){
        std::cout << arr[i] << " ";
    }
    //outputs 1 1 3 4 4 5 9
    return 0;
}
