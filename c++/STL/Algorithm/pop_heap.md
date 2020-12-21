# pop_heap

## 头文件
```cpp
#include  <algorithm>
```

## 函数原型:

```cpp
emplate< class RandomIt >
constexpr void pop_heap( RandomIt first, RandomIt last );

// 函数重载
template< class RandomIt, class Compare >
constexpr void pop_heap( RandomIt first, RandomIt last, Compare comp );
```

## 作用
此函数用于删除堆的最大元素。


## Example
  
 ```cpp
#include <algorithm> 
#include <iostream> 
#include <vector>

int main() {
    
    std::vector<int> v = {2,5,8,7,4,5};
    
    //converting vector into heap
    make_heap(v.begin(),v.end());
    //printing first element
    std::cout << "first element of the heap: " << v.front() << std::endl;
    //outputs 8
    
    for(auto n : v)
        std::cout << n << ' ';
    std::cout << '\n';
    
    pop_heap(v.begin(),v.end());
    //pops the maximum element in the heap
    //printing frist element
    std::cout << "first element of the heap after using pop_heap: " << v.front() << std::endl;
    
    for(auto n : v)
        std::cout << n << ' ';
    std::cout << '\n';
    
    return 0;
} 
 ```
**[See Example](snippets/pop_heap.cpp)**    

**[Run Code](https://rextester.com/LZFC20489)**