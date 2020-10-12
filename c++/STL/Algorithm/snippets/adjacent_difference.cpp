#include <iostream>     // std::cout
#include <vector>       // std::vector
#include <functional>   // std::plus
#include <numeric>      // std::adjacent_difference

int myOp (int x, int y) {
    return x+y;
}

int main () {

   std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
   std::adjacent_difference(v.begin(), v.end(), v.begin());  // 计算 v[first, last) 中相邻元素的差值
 
   for (auto n : v)
        std::cout << n << ' ';
      
   std::cout << '\n';
   // ouput :   1 1 1 1 1 1 1 1 1 1
 
   std::vector<int> res(v.size(),0);
   std::adjacent_difference(v.begin(), v.end(), res.begin(),  std::plus<> {});  // std::plus<>{} defined in header <functional>
   for (auto n : res)
        std::cout << n << ' ';
      
   std::cout << '\n';
   // output  : 1 2 2 2 2 2 2 2 2 2

	std::adjacent_difference (v.begin(), v.end(), res.begin(), myOp);					  // myOp is a customized function defined for addition
	std::cout << "using custom function: ";
	 for (auto n : res)
        std::cout << n << ' ';
	std::cout << '\n';
  // output : using custom function: 1 2 2 2 2 2 2 2 2 2
  	return 0;
}
