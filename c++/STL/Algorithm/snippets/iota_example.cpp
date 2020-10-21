#include <iostream>
#include <numeric>

int main()
{
    int arr[10];
    //Initialising the starting value as 500
    int num = 500;
    //Applying the function iota to each element
    std::iota(arr, arr + 10, num);
    // Printing the final output
    for(int i = 0; i < 10; i++)
    	std::cout << arr[i] <<" ";
    std::cout << std::endl;
    // output : 500 501 502 503 504 505 506 507 508 509 
    return 0;
}