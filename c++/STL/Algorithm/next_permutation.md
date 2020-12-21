# next_permutation

## 头文件
```cpp
#include  <algorithm>
```

## 函数原型:

```cpp
template< class BidirIt >
constexpr bool next_permutation( BidirIt first, BidirIt last );

// 函数重载，使用自定义的比较函数comp
template< class BidirIt, class Compare >
constexpr bool next_permutation( BidirIt first, BidirIt last, Compare comp );
```

## 作用
它用于将[`first`，`last`）范围内的元素重新排列为下一个“按字典顺序更大”的排列。如果不能以产生词典上更大的新范围的方式重新排列范围，则即使存在可能的重新排列，该范围也将返回`false`。这就是为什么最好对元素进行排序。对于`N`个元素，可能会有`N！`（阶乘）排列。

## 函数原型
```c++
template<class BidirIt>
bool next_permutation(BidirIt first, BidirIt last)
{
    if (first == last) return false;
    BidirIt i = last;
    if (first == --i) return false;
 
    while (true) {
        BidirIt i1, i2;
 
        i1 = i;
        if (*--i < *i1) {
            i2 = last;
            while (!(*i < *--i2))
                ;
            std::iter_swap(i, i2);
            std::reverse(i1, last);
            return true;
        }
        if (i == first) {
            std::reverse(first, last);
            return false;
        }
    }
}
```

## Example
  
 ```cpp
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
 ```

**[Run Code](https://rextester.com/ODMT74583)**