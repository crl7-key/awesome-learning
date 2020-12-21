#include <iostream>     // std::cout
#include <algorithm>    // std::next_permutation, std::sort
#include <string>

int main () {
  int integers[] = {1,2,3,4};
  std::sort(integers, integers + 4);
  std::cout<< "Before loop: "<< integers[0] << ' ' << integers[1] << ' ' << integers[2] << ' ' << integers[3] << '\n';
  std::cout << "showing all 4! permutations: \n";
  do {
    std::cout << integers[0] << ' ' << integers[1] << ' ' << integers[2] << ' ' << integers[3] << '\n';
  } while ( std::next_permutation(integers,integers+4) );

  std::cout << "After loop: " << integers[0] << ' ' << integers[1] << ' ' << integers[2] << ' ' << integers[3] << '\n';

  // 打印字符串 "aba" 的全部三种排列
  std::string s = "aba";
  std::sort(s.begin(), s.end());
    do {
        std::cout << s << '\n';
    } while(std::next_permutation(s.begin(), s.end()));
  return 0;
} 