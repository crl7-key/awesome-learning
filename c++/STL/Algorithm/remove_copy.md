# remove_copy

## 头文件
```cpp
#include  <algorithm>
```

## 函数原型:

```cpp
template< class InputIt, class OutputIt, class T >
constexpr OutputIt remove_copy( InputIt first, InputIt last, OutputIt d_first,
                                const T& value );

// 函数重载
template< class InputIt, class OutputIt, class UnaryPredicate >
constexpr OutputIt remove_copy_if( InputIt first, InputIt last, OutputIt d_first,
                                   UnaryPredicate p );
```

## 作用
移除 [`first`, `last`) 之中所有与 `value `相等的元素。它并不真正从容器中删除那些元素，而是将结果复制到一个以`result`标示起始位置的容器身上。

## 函数实现
```c++
template<class InputIt, class OutputIt, class T>
OutputIt remove_copy(InputIt first, InputIt last,
                     OutputIt d_first, const T& value)
{
    for (; first != last; ++first) {
        if (!(*first == value)) {
            *d_first++ = *first;
        }
    }
    return d_first;
}


// 函数重载,使用自定义的函数p
template<class InputIt, class OutputIt, class UnaryPredicate>
OutputIt remove_copy_if(InputIt first, InputIt last,
                        OutputIt d_first, UnaryPredicate p)
{
    for (; first != last; ++first) {
        if (!p(*first)) {
            *d_first++ = *first;
        }
    }
    return d_first;
}
```

## Example
  
```cpp
#include <iostream>     // std::cout
#include <algorithm>    
#include <vector>       // std::vector

int main () {
    std::vector<int> origin {3, 5, 3, 1, 2, 3};
    std::vector<int> destination;

    // Copy elements to destination that are not 3
    std::remove_copy(origin.begin(), //first
                     origin.end(),   //last
                     std::back_inserter(destination), //d_first 
                     3);
    
    // origin is still {3, 5, 3, 1, 2, 3}
    for (auto value : origin) { 
        std::cout << value << " "; 
    }
    std::cout << std::endl;

    // destination is {5, 1, 2}
    for (auto value : destination) { 
        std::cout << value << " "; 
    }
    std::cout << std::endl;

    return 0;
}
```
**[See Example](snippets/remove_copy.cpp)**    

**[Run Code](https://rextester.com/XAJF25328)**