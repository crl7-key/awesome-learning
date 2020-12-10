# Merge

## 头文件
```cpp
#include  <algorithm>
```

## 函数原型:

```cpp
template< class InputIt1, class InputIt2, class OutputIt >
constexpr OutputIt merge( InputIt1 first1, InputIt1 last1,
                          InputIt2 first2, InputIt2 last2,
                          OutputIt d_first );

// 函数重载
template< class InputIt1, class InputIt2, class OutputIt, class Compare>
constexpr OutputIt merge( InputIt1 first1, InputIt1 last1,
                          InputIt2 first2, InputIt2 last2,
                          OutputIt d_first, Compare comp );
```

## 作用
归并二个已排序范围 [`first1`, `last1`) 和 [`first2`, `last2`) 到始于 `d_first`的一个已排序范围中。

```cpp
template<class InputIt1, class InputIt2, class OutputIt>
OutputIt merge(InputIt1 first1, InputIt1 last1,
               InputIt2 first2, InputIt2 last2,
               OutputIt d_first)
{
    for (; first1 != last1; ++d_first) {
        if (first2 == last2) {
            return std::copy(first1, last1, d_first);
        }
        if (*first2 < *first1) {
            *d_first = *first2;
            ++first2;
        } else {
            *d_first = *first1;
            ++first1;
        }
    }
    return std::copy(first2, last2, d_first);
}
// 函数重载，使用自定义的comp函数
template<class T, class Compare> 
const T& max(const T& a, const T& b, Compare comp)
{
    return (comp(a, b)) ? b : a;
}

template< class T >
T max( std::initializer_list<T> ilist)
{
    return *std::max_element(ilist.begin(), ilist.end());
}
// 函数重载，使用自定义的comp函数
template<class InputIt1, class InputIt2,
         class OutputIt, class Compare>
OutputIt merge(InputIt1 first1, InputIt1 last1,
               InputIt2 first2, InputIt2 last2,
               OutputIt d_first, Compare comp)
{
    for (; first1 != last1; ++d_first) {
        if (first2 == last2) {
            return std::copy(first1, last1, d_first);
        }
        if (comp(*first2, *first1)) {
            *d_first = *first2;
            ++first2;
        } else {
            *d_first = *first1;
            ++first1;
        }
    }
    return std::copy(first2, last2, d_first);
}
```

## Example
  
 ```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<int> v1 {8, 2, 0, 4};
    std::vector<int> v2 {7, 3, 5};
    
    std::vector<int> destination(v1.size() + v2.size());

    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());

    std::merge(v1.begin(), v1.end(), // first range 
               v2.begin(), v2.end(), // second range
               destination.begin());

    for (auto value : destination) { 
        std::cout << value << " ";  // output : 0, 2, 3, 4, 5, 7, 8
    }
    
    return 0;
}
 ```
