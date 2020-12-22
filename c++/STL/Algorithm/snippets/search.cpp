#include <vector>
#include <iostream>
#include <algorithm>
 
int main()
{
   std::vector<int> vec {10, 20, 30, 40, 50, 60, 70, 80, 90};
   int arr[] = {40,50,60,70};
    
   std::vector<int>::iterator it;
    
   it = std::search (vec.begin(), vec.end(), arr, arr + 4);
    
   if (it != vec.end()){
     std::cout << "arr found at position " << (it - vec.begin()) << '\n';
   }
   else{
     std::cout << "arr not found\n";
   }
    
    return 0;
}