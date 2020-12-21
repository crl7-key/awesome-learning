# remove_if

## 头文件
```cpp
#include  <algorithm>
```

## 函数原型:

```cpp
template< class ForwardIt, class UnaryPredicate >
constexpr ForwardIt remove_if( ForwardIt first, ForwardIt last, UnaryPredicate p );
```

## 作用
移除 [`first`, `last`) 区间内所有被仿函数`pred`认定为`true`的元素，每一个不符合`pred`条件的元素都会被轮番赋值给`first`之后的空间。

## 函数实现
```c++
template<class ForwardIt, class UnaryPredicate>
ForwardIt remove_if(ForwardIt first, ForwardIt last, UnaryPredicate p)
{
    first = std::find_if(first, last, p);
    if (first != last)
        for(ForwardIt i = first; ++i != last; )
            if (!p(*i))
                *first++ = std::move(*i);
    return first;
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
**[See Example](snippets/remove_if.cpp)**    

**[Run Code](https://rextester.com/ZFJH99004)**