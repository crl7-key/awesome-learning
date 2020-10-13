# all_of

## 头文件
```cpp
#include <algorithm>
```

## 函数原型:

```cpp
template< class InputIt, class UnaryPredicate >
constexpr bool all_of( InputIt first, InputIt last, UnaryPredicate p );

```

## 作用
 第一个原型用来在范围内搜索 [first, last) 两个连续的相等元素的第一个元素。
 ```cpp
template<class ForwardIt>
ForwardIt adjacent_find(ForwardIt first, ForwardIt last)
{
    if (first == last) {
        return last;
    }
    ForwardIt next = first;
    ++next;
    for (; next != last; ++next, ++first) {
        if (*first == *next) {
            return first;
        }
    }
    return last;
}
 ```
 第二个原型相当于函数重载,最后一个参数是为改变查找相邻元素值相等运算而加载的二元函数,就是让二元函数取代默认的查找相邻元素值相等运算,即可以自定义回调函数。
```cpp
template<class ForwardIt, class BinaryPredicate>
ForwardIt adjacent_find(ForwardIt first, ForwardIt last, 
                        BinaryPredicate p)
{
    if (first == last) {
        return last;
    }
    ForwardIt next = first;
    ++next;
    for (; next != last; ++next, ++first) {
        if (p(*first, *next)) {
            return first;
        }
    }
    return last;
}
```

  ## Example
  ```cpp
int main()
{
   std::vector<int> v{ 1, 2, 3, 3, 4, 3, 7, 8, 9, 10 };
   auto i  = std::adjacent_find(v.begin(), v.end());  // 搜索 v[first, last) 中两个连续的相等元素的第一个元素。
  
   std::cout << "The first pair of repeated elements are: " << *i <<'\n';

   // ouput :  The first pair of repeated elements are: 3
   
   auto i2 = std::adjacent_find(v.begin(), v.end(), std::greater<int>());
   if (i2 == v.end()) {
        std::cout << "The entire vector is sorted in ascending order\n";
    } else {
        std::cout << "The last element in the non-decreasing subsequence is at: "
                  << std::distance(v.begin(), i2) << '\n';
    }
   
   // output : The last element in the non-decreasing subsequence is at: 4
   return 0;
}
  
  ```
  
