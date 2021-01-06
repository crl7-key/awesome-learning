# set_intersection

## 头文件
```cpp
#include  <algorithm>
```

## 函数原型:

```cpp
template< class InputIt1, class InputIt2, class OutputIt >
constexpr OutputIt set_intersection( InputIt1 first1, InputIt1 last1,
                                     InputIt2 first2, InputIt2 last2,
                                     OutputIt d_first );

// 函数重载, 使用自定义的函数comp
template< class InputIt1, class InputIt2,
                    class OutputIt, class Compare >
constexpr OutputIt set_intersection( InputIt1 first1, InputIt1 last1,
                                     InputIt2 first2, InputIt2 last2,
                                     OutputIt d_first, Compare comp );                                   
```

## 作用
构造一个排序范围，该范围从结果通过的位置开始，与两个排序范围[`first1`，`last1`）和[`first2`，`last2`）的交集相交


## 函数实现
```c++
template<class InputIt1, class InputIt2, class OutputIt>
OutputIt set_intersection(InputIt1 first1, InputIt1 last1,
                          InputIt2 first2, InputIt2 last2,
                          OutputIt d_first)
{
    while (first1 != last1 && first2 != last2) {
        if (*first1 < *first2) {
            ++first1;
        } else  {
            if (!(*first2 < *first1)) {
                *d_first++ = *first1++;
            }
            ++first2;
        }
    }
    return d_first;
}

// 函数重载，使用自定义的函数comp
template<class InputIt1, class InputIt2,
         class OutputIt, class Compare>
OutputIt set_intersection(InputIt1 first1, InputIt1 last1,
                          InputIt2 first2, InputIt2 last2,
                          OutputIt d_first, Compare comp)
{
    while (first1 != last1 && first2 != last2) {
        if (comp(*first1, *first2)) {
            ++first1;
        } else {
            if (!comp(*first2, *first1)) {
                *d_first++ = *first1++;
            }
            ++first2;
        }
    }
    return d_first;
}
```

## Example
  
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
int main()
{
    std::vector<int> v1 {1,2,3,4,5,6,7,8};
    std::vector<int> v2 {        5,  7,  9,10};

    // the destination needs to fit all merged values, we'll prune the extra elements later
    std::vector<int> destination(v1.size() + v2.size());

    // set_union requires sorted ranges
    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());

    // returns iterator to the end of the constructed range
    auto it = std::set_intersection(v1.begin(), v1.end(),  // first range 
                                    v2.begin(), v2.end(),  // second range
                                    destination.begin());

    // prune extra values
    destination.resize(it - destination.begin()); 

    // destination is now {5,7}
    for (auto value : destination) { 
        std::cout << value << " "; 
    }
    return 0;
}
```
**[See Example](snippets/set_intersection.cpp)**    

**[Run Code](https://rextester.com/NCEHCB91307)**