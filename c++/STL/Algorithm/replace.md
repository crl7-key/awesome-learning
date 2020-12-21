# replace

## 头文件
```cpp
#include  <algorithm>
```

## 函数原型:

```cpp
template< class ForwardIt, class T >
constexpr void replace( ForwardIt first, ForwardIt last,
                        const T& old_value, const T& new_value );
```

## 作用
用[`first`，`last`）范围内的`new_value`替换所有等于`old_value`的元素

## 函数实现
```c++
template<class ForwardIt, class T>
void replace(ForwardIt first, ForwardIt last,
             const T& old_value, const T& new_value)
{
    for (; first != last; ++first) {
        if (*first == old_value) {
            *first = new_value;
        }
    }
}
```

## Example
  
```cpp
#include <iostream>     // std::cout
#include <algorithm>    
#include <vector>       // std::vector

int main () {
    std::vector<int> origin {3, 5, 3, 1, 2, 3};

    // replaces 3 by 0
    std::replace(origin.begin(), //first
                 origin.end(),   //last
                 3,              //old_vale 
                 0               //new_value 
                 );
    
    // origin is now {0, 5, 0, 1, 2, 0}
    for (auto value : origin) { 
        std::cout << value << " "; 
    }
    return 0;
}

```
**[See Example](snippets/replace.cpp)**    

**[Run Code](https://rextester.com/LXDW34883)**