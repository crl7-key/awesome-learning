# search_n

## 头文件
```cpp
#include  <algorithm>
```

## 函数原型:

```cpp
template< class ForwardIt, class Size, class T >
constexpr ForwardIt search_n( ForwardIt first, ForwardIt last, Size count, const T& value );

// 函数重载
template< class ForwardIt, class Size, class T, class BinaryPredicate >
constexpr ForwardIt search_n( ForwardIt first, ForwardIt last, Size count, const T& value,
                               BinaryPredicate p );                                               
```

## 作用
在序列 [`first`, `last`) 所涵盖的区间中，查找连续`count`个符合条件之元素所形成的子序列，并返回一个迭代器指向该子序列起始处。

## 函数实现
```c++
template<class ForwardIt, class Size, class T>
ForwardIt search_n(ForwardIt first, ForwardIt last,
                    Size count, const T& value)
{
    if (count <= 0) {
        return first;
    }
 
    for(; first != last; ++first) {
        if (!(*first == value)) {
            continue;
        }
 
        ForwardIt candidate = first;
        Size cur_count = 0;
 
        while (true) {
            ++cur_count;
            if (cur_count >= count) {
                // 成功
                return candidate;
            }
            ++first;
            if (first == last) {
                // 穷尽列表
                return last;
            }
            if (!(*first == value)) {
                // 栏中过少
                break;
            }
        }
    }
    return last;
}

// 函数重载，使用自定义的函数p
template<class ForwardIt, class Size, class T, class BinaryPredicate>
ForwardIt search_n(ForwardIt first, ForwardIt last,
                    Size count, const T& value, BinaryPredicate p)
{
    if (count <= 0) {
        return first;
    }
 
    for(; first != last; ++first) {
        if (!p(*first, value)) {
            continue;
        }
 
        ForwardIt candidate = first;
        Size cur_count = 0;
 
        while (true) {
            ++cur_count;
            if (cur_count >= count) {
                // 成功
                return candidate;
            }
            ++first;
            if (first == last) {
                // 穷尽列表
                return last;
            }
            if (!p(*first, value)) {
                // 栏中过少
                break;
            }
        }
    }
    return last;
}
```

## Example
  
```cpp
#include<iostream>
#include<vector>
#include<algorithm>

int main() {
    // Sequence to search in
    std::vector<int> vec = { 7, 6, 0, 4, 4, 9, 3, 4, 8 }; 
  
    // Value to be searched for 
    int v1 = 4;

    // Number of successive elements
    int v2 = 2;

    // Iterator for storing the returning pointer 
    std::vector<int>::iterator it; 

    it = std::search_n(vec.begin(), vec.end(), v2, v1); 
  
    // checking if iterator it contains end pointer of v1 or not 
    if (it != vec.end()) { 
        std::cout << "v1 is present consecutively 2 times at index "
             << (it - vec.begin()); 
    } else { 
        std::cout << "v1 is not present consecutively 2 times in "
             << "vector vec"; 
    }
    return 0;
}
```
**[See Example](snippets/search_n.cpp)**    

**[Run Code](https://rextester.com/LLER97318)**