# replace_if

## 头文件
```cpp
#include  <algorithm>
```

## 函数原型:

```cpp
template< class ForwardIt, class UnaryPredicate, class T >
constexpr void replace_if( ForwardIt first, ForwardIt last,
                           UnaryPredicate p, const T& new_value );
```

## 作用
将 [`first`, `last`) 区间内的所有被`pred`评估为`true`的元素，都以`new_value`取而代之。

## 函数实现
```c++
template<class ForwardIt, class UnaryPredicate, class T>
void replace_if(ForwardIt first, ForwardIt last,
                UnaryPredicate p, const T& new_value)
{
    for (; first != last; ++first) {
        if(p(*first)) {
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
    auto isOdd = [](int i) {
        return ((i%2) == 1);
    };

    std::vector<int> origin {1, 2, 3, 4, 5};

    // replaces values for which isOdd returns true by 0
    std::replace_if(origin.begin(), //first
                 origin.end(),   //last
                 isOdd,          //condition 
                 0               //new_value 
                 );
    
    // origin is now {0, 2, 0, 4, 0}
    for (auto value : origin) { 
        std::cout << value << " "; 
    }
    return 0;
}
```
**[See Example](snippets/replace_if.cpp)**    

**[Run Code](https://rextester.com/GBW22594)**