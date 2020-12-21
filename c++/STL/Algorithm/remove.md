# remove

## 头文件
```cpp
#include  <algorithm>
```

## 函数原型:

```cpp
template< class ForwardIt, class T >
constexpr ForwardIt remove( ForwardIt first, ForwardIt last, const T& value );

// 函数重载
template< class ForwardIt, class UnaryPredicate >
constexpr ForwardIt remove_if( ForwardIt first, ForwardIt last, UnaryPredicate p );
```

## 作用
移除 [`first`, `last`) 之中所有与`value`相等的元素，这一算法并不真正从容器中删除那些元素，而是将每一个不与`value`相等的元素轮番赋值给`first`之后的空间

## 函数实现
```c++
template< class ForwardIt, class T >
ForwardIt remove(ForwardIt first, ForwardIt last, const T& value)
{
    first = std::find(first, last, value);
    if (first != last)
        for(ForwardIt i = first; ++i != last; )
            if (!(*i == value))
                *first++ = std::move(*i);
    return first;
}


// 函数重载,使用自定义的函数p
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
    std::vector<int> v {3, 5, 3, 1, 2, 3};

    // removes all elements that are 3
    auto newEndIt = std::remove(v.begin(), v.end(), 3);
    
    // Erase elements from [newEndIt, v.end()]
    v.erase(newEndIt, v.end());

    // v is now {5, 1, 2}
    for (auto value : v) { 
        std::cout << value << " "; 
    }

    return 0;
}
```
**[See Example](snippets/remove.cpp)**    

**[Run Code](https://rextester.com/ZRRHJP53083)**