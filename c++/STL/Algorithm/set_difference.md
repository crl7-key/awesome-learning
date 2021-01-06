# set_difference

## 头文件
```cpp
#include  <algorithm>
```

## 函数原型:

```cpp
template< class InputIt1, class InputIt2, class OutputIt >
constexpr OutputIt set_difference( InputIt1 first1, InputIt1 last1,
                                   InputIt2 first2, InputIt2 last2,
                                   OutputIt d_first );

// 函数重载, 使用自定义的函数comp
template< class InputIt1, class InputIt2,
          class OutputIt, class Compare >
constexpr OutputIt set_difference( InputIt1 first1, InputIt1 last1,
                                   InputIt2 first2, InputIt2 last2,
                                   OutputIt d_first, Compare comp );                                       
```

## 作用
构造一个排序范围，该范围从结果传递的位置开始，相对于另一个排序范围[`first2`，`last2`），排序范围[`first1`，`last1`）的差值

## 函数实现
```c++
template<class InputIt1, class InputIt2, class OutputIt>
OutputIt set_difference(InputIt1 first1, InputIt1 last1,
                        InputIt2 first2, InputIt2 last2,
                        OutputIt d_first)
{
    while (first1 != last1) {
        if (first2 == last2) return std::copy(first1, last1, d_first);
 
        if (*first1 < *first2) {
            *d_first++ = *first1++;
        } else {
            if (! (*first2 < *first1)) {
                ++first1;
            }
            ++first2;
        }
    }
    return d_first;
}

// 函数重载，使用自定义的函数comp
template<class InputIt1, class InputIt2,
         class OutputIt, class Compare>
OutputIt set_difference( InputIt1 first1, InputIt1 last1,
                         InputIt2 first2, InputIt2 last2,
                         OutputIt d_first, Compare comp)
{
    while (first1 != last1) {
        if (first2 == last2) return std::copy(first1, last1, d_first);
 
        if (comp(*first1, *first2)) {
            *d_first++ = *first1++;
        } else {
            if (!comp(*first2, *first1)) {
                ++first1;
            }
            ++first2;
        }
    }
    return d_first;
}
```

## Example
  
```cpp
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
```
**[See Example](snippets/set_difference.cpp)**    

**[Run Code](https://rextester.com/OZGO43021)**