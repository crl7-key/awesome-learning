# min_element

## 头文件
```cpp
#include  <algorithm>
```

## 函数原型:

```cpp
template< class ForwardIt >
constexpr ForwardIt min_element( ForwardIt first, ForwardIt last );

// 函数重载
template< class ForwardIt, class Compare >
constexpr ForwardIt min_element( ForwardIt first, ForwardIt last, Compare comp );
```

## 作用
寻找范围 [`first`, `last`) 中的最小元素。

```cpp
template<class ForwardIt>
ForwardIt min_element(ForwardIt first, ForwardIt last)
{
    if (first == last) return last;
 
    ForwardIt smallest = first;
    ++first;
    for (; first != last; ++first) {
        if (*first < *smallest) {
            smallest = first;
        }
    }
    return smallest;
}
// 函数重载，使用自定义的comp函数
template<class ForwardIt, class Compare>
ForwardIt min_element(ForwardIt first, ForwardIt last, Compare comp)
{
    if (first == last) return last;
 
    ForwardIt smallest = first;
    ++first;
    for (; first != last; ++first) {
        if (comp(*first, *smallest)) {
            smallest = first;
        }
    }
    return smallest;
}
```

## Example
  
 ```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<int> vec = {3, -1, 2, 10, 4};

    auto smallestIt = std::min_element(vec.begin(), vec.end()); 
   
    std::cout << "The smallest element is " << *smallestIt << std::endl; // outpu: -1
    return 0;
}
 ```

 **[Run Code](https://rextester.com/QLBFFX41641)**
