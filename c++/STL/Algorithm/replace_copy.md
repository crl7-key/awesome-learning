# replace_copy

## 头文件
```cpp
#include  <algorithm>
```

## 函数原型:

```cpp
template< class InputIt, class OutputIt, class T >
constexpr OutputIt replace_copy( InputIt first, InputIt last, OutputIt d_first,
                                 const T& old_value, const T& new_value );
```

## 作用

将范围从[`first`，`last`）的元素复制到以`d_first`开始的另一个范围，并用`new_value`替换与`old_value`匹配的元素

## 函数实现
```c++
template<class InputIt, class OutputIt, class T>
OutputIt replace_copy(InputIt first, InputIt last, OutputIt d_first,
                      const T& old_value, const T& new_value)
{
    for (; first != last; ++first) {
        *d_first++ = (*first == old_value) ? new_value : *first;
    }
    return d_first;
}
```

## Example
  
```cpp
//g++  7.4.0
#include <iostream>     // std::cout
#include <algorithm>    
#include <vector>       // std::vector

int main () {
    std::vector<int> origin {3, 5, 3, 1, 2, 3};
    std::vector<int> destination;

    // Copy elements to destination replacing elements that are 3 by 0
    std::replace_copy(origin.begin(),                  //first
                      origin.end(),                    //last
                      std::back_inserter(destination), //d_first 
                      3,                               //old_value
                      0                                //new_value
                      );
    
    // origin is still {3, 5, 3, 1, 2, 3}
    for (auto value : origin) { 
        std::cout << value << " "; 
    }
    std::cout << std::endl;

    // destination is {0, 5, 0, 1, 2, 0}
    for (auto value : destination) { 
        std::cout << value << " "; 
    }
    std::cout << std::endl;
    return 0;
}
```
**[See Example](snippets/replace_copy.cpp)**    

**[Run Code](https://rextester.com/LSLGSA62675)**