# max_element

## 头文件
```cpp
#include  <algorithm>
```


## 函数原型:

```cpp
template< class ForwardIt >
constexpr ForwardIt max_element(ForwardIt first, ForwardIt last );

// 函数重载
template< class ForwardIt, class Compare >
constexpr ForwardIt max_element(ForwardIt first, ForwardIt last, Compare comp );
```

## 作用
返回由 [ `first`，`last`）定义的范围内最大元素的迭代器。

```cpp
template<class ForwardIt>
ForwardIt max_element(ForwardIt first, ForwardIt last)
{
    if (first == last) {
        return last;
    }
    ForwardIt largest = first;
    ++first;
    for (; first != last; ++first) {
        if (*largest < *first) {
            largest = first;
        }
    }
    return largest;
}

// 函数重载，使用自定义的comp函数
template<class ForwardIt, class Compare>
ForwardIt max_element(ForwardIt first, ForwardIt last, 
                      Compare comp)
{
    if (first == last) {
        return last;
    }
    ForwardIt largest = first;
    ++first;
    for (; first != last; ++first) {
        if (comp(*largest, *first)) {
            largest = first;
        }
    }
    return largest;
}
```

## Example
  
 ```cpp
#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> data = {3, -1, 2, 10, 4};

    auto greatestIt = std::max_element(data.begin(), data.end()); 
    
    std::cout << "The greatest element is " << *greatestIt << std::endl; // output: 10
    return 0;
}
 ```

 **[Run Code](https://rextester.com/TAZ1543)**
