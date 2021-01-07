#include <iostream>
#include <string_view>

int main()
{
   int a = 5, b = 3;
 
   // 前
   std::cout << a << ' ' << b << '\n';
 
   std::swap(a,b);
 
   // 后
   std::cout << a << ' ' << b << '\n';
   
   return 0;
}