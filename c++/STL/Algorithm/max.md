# Max

## 头文件
```cpp
#include  <algorithm>
```

## 函数原型:

```cpp
template< class T >
constexpr const T& max( const T& a, const T& b );


template< class T >
constexpr T max( std::initializer_list<T> ilist );

// 函数重载
template< class T, class Compare >
constexpr const T& max( const T& a, const T& b, Compare comp );

template< class T, class Compare >
constexpr T max( std::initializer_list<T> ilist, Compare comp );
```

## 作用
比较两个值，返回最大值。

```cpp
template<class T> 
const T& max(const T& a, const T& b)
{
    return (a < b) ? b : a;
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
template< class T, class Compare >
T max( std::initializer_list<T> ilist, Compare comp )
{
    return *std::max_element(ilist.begin(), ilist.end(), comp);
}
```

## Example
  
 ```cpp
int main()
#include <algorithm>
#include <iostream>

int main()
{
    int a = 7, b = 3;
    auto greatest = std::max(a,b);
    std::cout << greatest << std::endl;  // output : 7
    return 0;
}
 ```

 **[Run Code](https://rextester.com/ORN25451)**
