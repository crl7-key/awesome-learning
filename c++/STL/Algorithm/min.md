# Min

## 头文件
```cpp
#include  <algorithm>
```

## 函数原型:

```cpp
template< class T >
constexpr const T& min( const T& a, const T& b );

// 函数重载
template< class T, class Compare >
constexpr const T& min( const T& a, const T& b, Compare comp );


template< class T >
constexpr T min( std::initializer_list<T> ilist );

// 函数重载
template< class T, class Compare >
constexpr T min( std::initializer_list<T> ilist, Compare comp );
```

## 作用
比较两个值，返回最小值。

```cpp
template<class T> 
const T& min(const T& a, const T& b)
{
    return (b < a) ? b : a;
}
// 函数重载，使用自定义的comp函数
template<class T, class Compare> 
const T& min(const T& a, const T& b, Compare comp)
{
    return (comp(b, a)) ? b : a;
}

template< class T >
T max( std::initializer_list<T> ilist)
{
    return *std::max_element(ilist.begin(), ilist.end());
}
// 函数重载，使用自定义的comp函数
template<class T, class Compare>
T min(std::initializer_list<T> ilist, Compare comp)
{
    return *std::min_element(ilist.begin(), ilist.end(), comp);
}
```

## Example
  
 ```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    int a = 7, b = 3;
    auto smallest = std::min(a, b);
    
    std::cout << smallest << " "; // output : 3
    return 0;
}
 ```

**[Run Code](https://rextester.com/YDKDLZ34239)**