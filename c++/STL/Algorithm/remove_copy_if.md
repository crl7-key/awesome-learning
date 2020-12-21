# remove_copy_if

## 头文件
```cpp
#include  <algorithm>
```

## 函数原型:

```cpp
template< class InputIt, class OutputIt, class UnaryPredicate >
constexpr OutputIt remove_copy_if( InputIt first, InputIt last, OutputIt d_first,
                                   UnaryPredicate p );
```

## 作用
移除 [`first`, `last`) 区间内所有被仿函数`pred`认定为`true`的元素，它并不真正从容器中删除那些元素，而是将结果复制到一个以`result`标示起始位置的容器身上。将范围从[`first`，`last`）的元素复制到以`d_first`开始的另一个范围，并省略满足特定条件的元素

## 函数实现
```c++
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
    auto isOdd = [](int i) {
        return ((i%2) == 1);
    };

    std::vector<int> origin {1, 2, 3, 4, 5};
    std::vector<int> destination;

    // Copy elements to destination that return false for isOdd
    std::remove_copy_if(origin.begin(), //first
                        origin.end(),   //last
                        std::back_inserter(destination), //d_first 
                        isOdd);
    
    // origin is still {1, 2, 3, 4, 5}
    for (auto value : origin) { 
        std::cout << value << " "; 
    }
    std::cout << std::endl;

    // destination is {2, 4}
    for (auto value : destination) { 
        std::cout << value << " "; 
    }
    std::cout << std::endl;

    return 0;
}
```
**[See Example](snippets/remove_copy_if.cpp)**    

**[Run Code](https://rextester.com/EGNBJ33640)**