# reverse_copy

## 头文件
```cpp
#include  <algorithm>
```

## 函数原型:

```cpp
template< class BidirIt, class OutputIt >
constexpr OutputIt reverse_copy( BidirIt first, BidirIt last, OutputIt d_first );
```

## 作用
将序列 [`first`, `last`) 的元素在原容器中颠倒重排

## 函数实现
```c++
template<class BidirIt, class OutputIt>
OutputIt reverse_copy(BidirIt first, BidirIt last, OutputIt d_first)
{
    while (first != last) {
        *(d_first++) = *(--last);
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
    std::vector<int> v({1,2,3});
    for (const auto& value : v) {
        std::cout << value << " ";
    }
    std::cout << '\n';
 
    std::vector<int> destination(3);
    std::reverse_copy(std::begin(v), std::end(v), std::begin(destination));
    for (const auto& value : destination) {
        std::cout << value << " ";
    }
    std::cout << '\n';
    return 0;
}
```
**[See Example](snippets/reverse_copy.cpp)**    

**[Run Code](https://rextester.com/VVZX48534)**