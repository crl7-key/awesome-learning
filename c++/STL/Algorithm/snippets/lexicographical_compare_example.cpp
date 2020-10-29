#include <iostream>
#include <algorithm>

int main()
{
    std::string a[] = {"dog", "cat", "cow"};
        
    std::string b[] = {"dog","pigglet","cow"};
      
    if( std::lexicographical_compare(a,a+1,b,b+1)) { 
        std::cout << "True";          
    } 
    else {         
        std::cout << "False";           
    }                          
    return 0;
}