# lower_bound

## 头文件
```cpp
#include  <algorithm>
```


## 函数原型:

```cpp
template< class RandomIt >
constexpr void make_heap( RandomIt first, RandomIt last );

// 函数重载
template< class RandomIt, class Compare >
constexpr void make_heap( RandomIt first, RandomIt last,
                          Compare comp );
```

## 作用
在范围 `[first, last) `中构造最大堆。函数第一版本用`operator< `比较元素，第二版本用给定的比较函数`comp` 。


## Example
  
 ```cpp
#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::cout << "Max heap:" << std::endl;
 
    std::vector<int> data =  { 3, 2, 4, 1, 5, 9 };
    
    std::make_heap(data.begin(),data.end());
    
    std::cout << "The maximum element of heap is : "; 
    std::cout << data.front() << std::endl;  // output : 9
    
    // print heap
    for(int i = 0; i < data.size(); ++i) {
        std::cout << data[i] << " " ;
    }
    return 0;
}
 ```

 **[Run Code](https://rextester.com/JPL35699)**
