# replace_copy_if

## 头文件
```cpp
#include  <algorithm>
```

## 函数原型:

```cpp
template< class InputIt, class OutputIt, class UnaryPredicate, class T >
constexpr OutputIt replace_copy_if( InputIt first, InputIt last, OutputIt d_first,
                                    UnaryPredicate p, const T& new_value );
```

## 作用
将元素从[`first`，`last`）范围复制到另一个以`d_first`开始的范围，并用`new_value`替换满足特定条件的元素

## 函数实现
```c++
template<class InputIt, class OutputIt, 
         class UnaryPredicate, class T>
OutputIt replace_copy_if(InputIt first, InputIt last, OutputIt d_first,
                         UnaryPredicate p, const T& new_value)
{
    for (; first != last; ++first) {
        *d_first++ = p( *first ) ? new_value : *first;
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

    // Copy elements to destination replacing elements that return true for isOdd by 0
    std::replace_copy_if(origin.begin(),                  //first
                         origin.end(),                    //last
                         std::back_inserter(destination), //d_first 
                         isOdd,                           //condition
                         0                                //new_value
                         );
    
    // origin is still {1, 2, 3, 4, 5}
    for (auto value : origin) { 
        std::cout << value << " "; 
    }
    std::cout << std::endl;

    // destination is {0, 2, 0, 4, 0}
    for (auto value : destination) { 
        std::cout << value << " "; 
    }
    std::cout << std::endl;
    return 0;
}
```
**[See Example](snippets/replace_copy_if.cpp)**    

**[Run Code](https://rextester.com/VTAX32831)**