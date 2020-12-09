# lower_bound

## 头文件
```cpp
#include  <algorithm>
```


## 函数原型:

```cpp
template< class ForwardIt, class T >
constexpr ForwardIt lower_bound( ForwardIt first, ForwardIt last, const T& value );

// 函数重载
template< class ForwardIt, class T, class Compare >
constexpr ForwardIt lower_bound( ForwardIt first, ForwardIt last, const T& value, Compare comp );
```

## 作用
返回指向范围 [`first`, `last`) 中首个不小于（即大于或等于）`value`的元素的迭代器，或若找不到这种元素则返回`last`。

 ```cpp
template<class ForwardIt, class T>
ForwardIt lower_bound(ForwardIt first, ForwardIt last, const T& value)
{
    ForwardIt it;
    typename std::iterator_traits<ForwardIt>::difference_type count, step;
    count = std::distance(first, last);
 
    while (count > 0) {
        it = first; 
        step = count / 2; 
        std::advance(it, step);
        if (*it < value) {
            first = ++it; 
            count -= step + 1; 
        }
        else
            count = step;
    }
    return first;
}

// 函数重载,使用自定义的方法comp
template<class ForwardIt, class T, class Compare>
ForwardIt lower_bound(ForwardIt first, ForwardIt last, const T& value, Compare comp)
{
    ForwardIt it;
    typename std::iterator_traits<ForwardIt>::difference_type count, step;
    count = std::distance(first, last);
 
    while (count > 0) {
        it = first;
        step = count / 2;
        std::advance(it, step);
        if (comp(*it, value)) {
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
    std::vector<int> data = {3, -1, 2, 5, 10, 6, 7, 4};
    std::sort(data.begin(), data.end());
    
    auto lower = std::lower_bound(data.begin(),data.end(),8);
    
    std::cout << "The lower bound element is " << *lower << std::endl;
    return 0;
}
 ```

 **[Run Code](https://rextester.com/WCN67227)**
