# rotate

## 头文件
```cpp
#include  <algorithm>
```

## 函数原型:

```cpp
template< class ForwardIt >
constexpr ForwardIt
          rotate( ForwardIt first, ForwardIt n_first, ForwardIt last );
```

## 作用
将 [`first`, `n_first`) 内的元素和 [`n_first`, `last`) 内的元素互换，`n_first`所指的元素会成为容器的第一个元素。

## 函数实现
```c++
template<class ForwardIt>
ForwardIt rotate(ForwardIt first, ForwardIt n_first, ForwardIt last)
{
   if(first == n_first) return last;
   if(n_first == last) return first;
 
   auto read      = n_first;
   auto write     = first;
   auto next_read = first; // "read" 撞击 "last" 时的读取位置
 
   while(read != last) {
      if(write == next_read) next_read = read; // 跟踪 "first" 所至
      std::iter_swap(write++, read++);
   }
 
   // 旋转剩余序列到位置中
   (rotate)(write, next_read, last);
   return write;
}
```

## Example
  
```cpp
#include <vector>
#include <iostream>
#include <algorithm>
 
int main()
{
    std::vector<int> v{2, 4, 2, 0, 5, 10, 7, 3, 7, 1}; 
 
    std::cout << "before sort:      ";
    for (int n: v)
        std::cout << n << ' ';
    std::cout << '\n';
 
    // 插入排序
    for (auto i = v.begin(); i != v.end(); ++i) {
        std::rotate(std::upper_bound(v.begin(), i, *i), i, i+1);
    }
 
    std::cout << "after sort:       ";
    for (int n: v)
        std::cout << n << ' ';
    std::cout << '\n';
 
    // 简单地旋转到左侧
    std::rotate(v.begin(), v.begin() + 1, v.end());
 
    std::cout << "simple rotate left  : ";
    for (int n: v)
        std::cout << n << ' ';
    std::cout << '\n';
 
    // 简单地旋转到右侧
    std::rotate(v.rbegin(), v.rbegin() + 1, v.rend());
 
    std::cout << "simple rotate right : ";
    for (int n: v)
        std::cout << n << ' ';
    std::cout << '\n';
 
}
```
**[See Example](snippets/rotate.cpp)**    

**[Run Code](https://rextester.com/DWCG37344)**