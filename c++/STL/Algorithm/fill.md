# fill

## 头文件
```cpp
#include <algorithm>  
```

## 函数原型:

```cpp
template< class ForwardIt, class T >
constexpr void fill( ForwardIt first, ForwardIt last, const T& value );
```

## 作用
 将值`val`分配给 [first，last)范围内的所有元素，其中`first`是初始位置，`last`是最后位置。  
 
 ```cpp
template< class ForwardIt, class T >
void fill(ForwardIt first, ForwardIt last, const T& value)
{
    for (; first != last; ++first) {
        *first = value;
    }
}
 ```


  ## Example
  
 ```cpp
int main()
{
    std::vector<int> v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
 
    std::fill(v.begin(), v.end(), -1);
 
    for (auto elem : v) {
        std::cout << elem << " ";
    }
    std::cout << "\n";

    //output : -1 -1 -1 -1 -1 -1 -1 -1 -1 -1
    return 0;
}
 ```
