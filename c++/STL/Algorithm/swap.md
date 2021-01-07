# swap

## 头文件
```cpp
#include  <string_view>
```

## 函数原型:

```cpp
template< class T >
constexpr void swap( T& a, T& b ) noexcept


template< class T2, std::size_t N >
constexpr void swap( T2 (&a)[N], T2 (&b)[N]) noexcept
```


## 作用
交换两个对象的值

## Example
  
```cpp
#include <string_view>
#include <iostream>
 
int main()
{
   int a = 5, b = 3;
 
   // 前
   std::cout << a << ' ' << b << '\n';
 
   std::swap(a,b);
 
   // 后
   std::cout << a << ' ' << b << '\n';
   return 0;
}
```
**[See Example](snippets/swap.cpp)**    

**[Run Code](https://rextester.com/PENR49350)**