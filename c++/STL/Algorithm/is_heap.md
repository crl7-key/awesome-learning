# is_heap

## 头文件
```cpp
#include <algorithm>
```

## 函数原型:

```cpp
template< class RandomIt >
constexpr bool is_heap( RandomIt first, RandomIt last );

// 函数重载,使用自定义的函数方法comp
template< class RandomIt, class Compare >
constexpr bool is_heap( RandomIt first, RandomIt last, Compare comp );
```

## 作用
检查[first，last）范围内的元素是否是最大堆。 



## Example
  
 ```cpp
int main()
{
    std::vector<int> v { 3, 1, 4, 1, 5, 9 };
 
    std::cout << "initially, v: ";
    for (auto i : v) std::cout << i << ' ';
    std::cout << '\n';
    // output : initially, v: 3 1 4 1 5 9 
 
    if (!std::is_heap(v.begin(), v.end())) {
        std::cout << "making heap...\n";
        std::make_heap(v.begin(), v.end());
    }
 
    std::cout << "after make_heap, v: ";
    for (auto i : v) std::cout << i << ' ';
    std::cout << '\n';
    // after make_heap, v: 9 5 4 1 1 3
    return 0;
}
 ```
