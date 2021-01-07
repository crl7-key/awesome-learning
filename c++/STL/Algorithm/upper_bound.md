# upper_bound

## 头文件
```cpp
#include  <algorithm>
```

## 函数原型:

```cpp
template< class ForwardIt, class T >
constexpr ForwardIt upper_bound( ForwardIt first, ForwardIt last, const T& value );


// 函数重载
template< class ForwardIt, class T, class Compare >
constexpr ForwardIt upper_bound( ForwardIt first, ForwardIt last, const T& value, Compare comp );
```


## 作用
二分查找，在已排序的 [`first`, `last`) 中的寻找元素`value`，与`lower_bound`区别是返回查找值的位置。

## 可能的实现
```cpp
template<class ForwardIt, class T>
ForwardIt upper_bound(ForwardIt first, ForwardIt last, const T& value)
{
    ForwardIt it;
    typename std::iterator_traits<ForwardIt>::difference_type count, step;
    count = std::distance(first,last);
 
    while (count > 0) {
        it = first; 
        step = count / 2; 
        std::advance(it, step);
        if (!(value < *it)) {
            first = ++it;
            count -= step + 1;
        }
        else
            count = step;
    }
    return first;
}

// 函数重载
template<class ForwardIt, class T, class Compare>
ForwardIt upper_bound(ForwardIt first, ForwardIt last, const T& value, Compare comp)
{
    ForwardIt it;
    typename std::iterator_traits<ForwardIt>::difference_type count, step;
    count = std::distance(first,last);
 
    while (count > 0) {
        it = first; 
        step = count / 2;
        std::advance(it, step);
        if (!comp(value, *it)) {
            first = ++it;
            count -= step + 1;
        }
        else
            count = step;
    }
    return first;
}
```

## Example
  
```cpp
#include <algorithm>
#include <iostream>
#include <vector>
 
int main()
{
    std::vector<int> data = { 1, 2, 4, 5, 5, 6 };
 
    for (int i = 0; i < 7; ++i) {
        // 搜索首个大于 i 的元素
        auto upper = std::upper_bound(data.begin(), data.end(), i);
 
        std::cout << i << " < ";
        if (upper != data.end())
            std::cout << *upper << " at index " << std::distance(data.begin(), upper);
        else
            std::cout << "not found";
        std::cout << '\n';
    }
    return 0;
}
```
**[See Example](snippets/upper_bound.cpp)**    

**[Run Code](https://rextester.com/KBBZ88431)**