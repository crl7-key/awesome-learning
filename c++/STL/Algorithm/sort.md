# sort

## 头文件
```cpp
#include  <algorithm>
```

## 函数原型:

```cpp
template< class RandomIt >
constexpr void sort( RandomIt first, RandomIt last );

// 函数重载，使用自定义的函数comp
template< class RandomIt, class Compare >
constexpr void sort( RandomIt first, RandomIt last, Compare comp );
```


## 作用
此功能实现为快速排序。它的复杂度为`O（N * log（N）`

## Example
  
```cpp
#include <iostream>
#include <algorithm>


void show(int a[]) { 
    for(int i = 0; i < 10; ++i) 
        std::cout << a[i] << " "; 
} 
  
int main() {
    int a[10]= {1, 5, 8, 9, 6, 7, 3, 4, 2, 0}; 
    std::cout << "\n The array before sorting is : "; 
    show(a); 
  
    std::sort(a, a+10); 
  
    std::cout << "\n\n The array after sorting is : "; 
    show(a); 
  
    return 0; 
} 
```
**[See Example](snippets/sort.cpp)**    

**[Run Code](https://rextester.com/YSL34293)**