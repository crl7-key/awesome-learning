# copy_backward

## 头文件
```cpp
#include <algorithm> 
```

## 函数原型:

```cpp
template< class BidirIt1, class BidirIt2 >
constexpr BidirIt2 copy_backward( BidirIt1 first, BidirIt1 last, BidirIt2 d_last );

```


## 作用
将 [first, last) 区间内的每一个元素,以逆行的方向复制到以 result-1 为起点,方向亦为逆行的区间上。
 ```cpp
template< class BidirIt1, class BidirIt2 >
BidirIt2 copy_backward(BidirIt1 first, BidirIt1 last, BidirIt2 d_last)
{
    while (first != last) {
        *(--d_last) = *(--last);
    }
    return d_last;
}
```

  ## Example
  
 ```cpp
int main()
{
    std::vector<int> vec;
    for (int i = 0; i < 10; i++) {
        vec.push_back(i);
    }
    std::vector<int> res(15);

    std::copy_backward(vec.begin(), vec.end(), res.end());
    
    std::cout << "res contains: ";
    for (auto value : res) {  
        std::cout << value << " "; 
    }
    
    // output : res contains: 0 0 0 0 0 0 1 2 3 4 5 6 7 8 9
     return 0;
}
 ```
