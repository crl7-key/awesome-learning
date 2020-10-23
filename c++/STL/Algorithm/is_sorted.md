# is_sorted

## 头文件
```cpp
#include <numeric>
```

## 函数原型:

```cpp
template< class ForwardIt >
constexpr bool is_sorted( ForwardIt first, ForwardIt last );

// 函数重载
template< class ForwardIt, class Compare >
constexpr bool is_sorted( ForwardIt first, ForwardIt last, Compare comp );
```

## 作用
检查范围[first，last]中的元素是否按升序排序。 如果元素按升序排序，则函数返回true，否则返回false。

 ```cpp
template<class ForwardIt>
bool is_sorted(ForwardIt first, ForwardIt last)
{
    return std::is_sorted_until(first, last) == last;
}

// 函数重载,使用自定义的函数方法comp
template<class ForwardIt, class Compare>
bool is_sorted(ForwardIt first, ForwardIt last, Compare comp)
{
    return std::is_sorted_until(first, last, comp) == last;
}
 ```


## Example
  
 ```cpp
int main()
{
    int digits[] = {3, 1, 4, 1, 5};
 
    for (auto i : digits) std::cout << i << ' ';
    std::cout << ": is_sorted: " << std::boolalpha
              << std::is_sorted(std::begin(digits), std::end(digits)) << '\n';
              // output : 3 1 4 1 5 : is_sorted: false
    std::sort(std::begin(digits), std::end(digits));
 
    for (auto i : digits) std::cout << i << ' ';
    std::cout << ": is_sorted: "
              << std::is_sorted(std::begin(digits), std::end(digits)) << '\n';

              // output : 1 1 3 4 5 : is_sorted: true
    return 0;
}
 ```
