# equal_range(应用于有序区间)

## 头文件
```cpp
#include <algorithm>  
```

## 函数原型:

```cpp
template< class ForwardIt, class T >
constexpr std::pair<ForwardIt,ForwardIt>
              equal_range( ForwardIt first, ForwardIt last,
                           const T& value );
      
// 函数重载      
template< class ForwardIt, class T, class Compare >
constexpr std::pair<ForwardIt,ForwardIt>
              equal_range( ForwardIt first, ForwardIt last,
                           const T& value, Compare comp );
```

## 作用
 二分查找法的一个版本,试图在已排序的 [first, last) 中寻找 value。  
 
 ```cpp
template<class ForwardIt, class T>
std::pair<ForwardIt,ForwardIt> 
    equal_range(ForwardIt first, ForwardIt last,
                const T& value)
{
    return std::make_pair(std::lower_bound(first, last, value),
                          std::upper_bound(first, last, value));
}

// 函数重载,使用自定义的方法comp
template<class ForwardIt, class T, class Compare>
std::pair<ForwardIt,ForwardIt> 
    equal_range(ForwardIt first, ForwardIt last,
                const T& value, Compare comp)
{
    return std::make_pair(std::lower_bound(first, last, value, comp),
                          std::upper_bound(first, last, value, comp));
}
 ```


  ## Example
  
 ```cpp
int main()
{
    std::vector<int> vec = {1, 2, 3, 4, 6, 7};
    
    auto p = std::equal_range(vec.begin(), vec.end(), 1); 
    for (auto i = p.first; i != p.second; ++i) {
        std::cout << " p : " << (i - vec.begin()) << " = " << *it << std::endl;
    }
    
    std::vector<int> vec2 = {1, 2, 3, 1, 6, 1};
    // equal_range requires a sorted input {1, 1, 1, 2, 3, 6}
    std::sort(vec2.begin(), vec2.end());

    // returns pair of iterators for positions 0 and 2:
    // {1, 1, 1, 2, 3, 6}
    //  ^        ^
    auto equalRangeIt = std::equal_range(vec2.begin(), vec2.end(), 1); 
    for (auto it = equalRangeIt.first; it != equalRangeIt.second; ++it) {
        std::cout << " Position: " << (it - vec2.begin()) << " = " << *it << std::endl;
    }
}
 ```
