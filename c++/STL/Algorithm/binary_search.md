# binary_search ( (应用于有序空间))

## 头文件
```cpp
#include <algorithm>
```

## 函数原型:

```cpp
template< class ForwardIt, class T >
constexpr bool binary_search( ForwardIt first, ForwardIt last, const T& value );


template< class ForwardIt, class T, class Compare >
constexpr bool binary_search( ForwardIt first, ForwardIt last, const T& value, Compare comp );
```

## 作用
  第一个原型: 二分查找法，在已排序的 [first, last) 中的寻找元素 value，查找到，返回 true，否则 false。
```cpp
template<class ForwardIt, class T>
bool binary_search(ForwardIt first, ForwardIt last, const T& value)
{
    first = std::lower_bound(first, last, value);
    return (!(first == last) && !(value < *first));
}
```
 
    第二个原型:相当于函数重载,最后一个参数是使用给定的比较函数comp。
```cpp
template<class ForwardIt, class T, class Compare>
bool binary_search(ForwardIt first, ForwardIt last, const T& value, Compare comp)
{
    first = std::lower_bound(first, last, value, comp);
    return (!(first == last) && !(comp(value, *first)));
}
```

  ## Example
```cpp
void print(std::vector<int>& v) {
    for (auto p : v) {
        std::cout<< p << " ";
    }
    std::cout << std::endl;
}

int main(int argc, char const *argv[])
{
    std::vector<int> v {1, 3, 4, 5, 9};
    print(v);

    if (std::binary_search(v.begin(), v.end(), 3)) 
        std::cout << "Element found in the vector" << std::endl;
    else
        std::cout << "Element not found in the vector" << std::endl;

    // ouput : Element found in the vector

    auto fn = [](int a, int b){ return a > b;};

    if (std::binary_search (std::begin (v), std::end (v), 3, fn))
        std::cout << 3 << " is definitely in there - somewhere..."<< std:: endl;
    else
        std::cout << 3 << " cannot be found - maybe you got it wrong..."<< std::endl;

    // output : 3 cannot be found - maybe you got it wrong...

    return 0;
}
```
  
