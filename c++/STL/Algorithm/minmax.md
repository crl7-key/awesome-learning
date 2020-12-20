# minmax

## 头文件
```cpp
#include  <algorithm>
```

## 函数原型:

```cpp
template< class T >
constexpr std::pair<const T&,const T&> minmax( const T& a, const T& b );

// 函数重载
template< class T, class Compare >
constexpr std::pair<const T&,const T&> minmax( const T& a, const T& b,
                                               Compare comp );

// 返回 initializer_list ilist 中值的最小和最大者
template< class T >
constexpr std::pair<T,T> minmax( std::initializer_list<T> ilist);  


template< class T, class Compare >
constexpr std::pair<T,T> minmax( std::initializer_list<T> ilist, Compare comp );
```

## 作用
比较返回一对[`最小`,`最大`]的值。可用于值或容器。

```cpp
// 使用 operator< 比较值
template<class T> 
std::pair<const T&, const T&> minmax( const T& a, const T& b )
{
    return (b < a) ? std::pair<const T&, const T&>(b, a)
                   : std::pair<const T&, const T&>(a, b);
}
// 函数重载，使用自定义的comp函数
template<class T, class Compare> 
std::pair<const T&, const T&> minmax( const T& a, const T& b, Compare comp )
{
    return comp(b, a) ? std::pair<const T&, const T&>(b, a)
                      : std::pair<const T&, const T&>(a, b);
}
// 版本三 返回 initializer_list ilist 中值的最小和最大者
template< class T >
std::pair<T, T> minmax( std::initializer_list<T> ilist )
{
    auto p = std::minmax_element(ilist.begin(), ilist.end());
    return std::make_pair(*p.first, *p.second);
}
// 函数重载，使用自定义的comp函数,返回 initializer_list ilist 中值的最小和最大者
template< class T, class Compare >
std::pair<T, T> minmax( std::initializer_list<T> ilist, Compare comp )
{
    auto p = std::minmax_element(ilist.begin(), ilist.end(), comp);
    return std::make_pair(*p.first, *p.second);
}
```

## Example
  
 ```cpp
#include <iostream>
#include <algorithm>

int main()
{
    int a = 7, b = 3;
    
    // returns pair <3, 7>
    auto minMax1 = std::minmax(a, b);
    std::cout << "Min is " << minMax1.first <<
                 " Max is " << minMax1.second << std::endl;
                 
    // returns pair<1,9>
    auto minMax2 = std::minmax({3, 1, 4, 1, 5, 9, 2, 6});
    std::cout << "Min is " << minMax2.first <<
                 " Max is " << minMax2.second << std::endl;

    return 0;
}
 ```

**[Run Code](https://rextester.com/JQJFV45955)**