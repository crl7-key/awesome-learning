# nth_element

## 头文件
```cpp
#include  <algorithm>
```

## 函数原型:

```cpp
template< class RandomIt >
constexpr void nth_element( RandomIt first, RandomIt nth, RandomIt last );

// 函数重载
template< class RandomIt, class Compare >
constexpr void nth_element( RandomIt first, RandomIt nth, RandomIt last,
                            Compare comp );
```

## 作用
是一种`STL`算法，它以这样一种方式重新排列列表，使得如果我们对列表进行排序，则位于第`n`个位置的元素应该是应该位于该位置的元素。使第`n`大元素处于第`n`位置（从`0`开始,其位置是下标为`n`的元素），并且比这个元素小的元素都排在这个元素之前，比这个元素大的元素都排在这个元素之后，但不能保证他们是有序的。


## Example
  
 ```cpp
#include <algorithm> 
#include <iostream> 

int main() {
    
    // Creating array of size 8
    int v[] = { 3, 2, 10, 45, 33, 56, 23, 47 }, i; 
  
    // Using std::nth_element with n as 5 
    std::nth_element(v, v + 4, v + 8); 
  
    // Since, n is 5 so 5th element should be sorted 
    for (i = 0; i < 8; ++i) { 
        std::cout << v[i] << " "; 
    } 
    std::cout << std::endl;
    
    std::cout << "The median is " << v[(sizeof(v)/sizeof(v[0]))/2] << '\n';
    
    return 0;
} 
 ```
**[See Example](snippets/nth_element.cpp)**    

**[Run Code](https://rextester.com/HPEUT47715)**