# reverse

## 头文件
```cpp
#include  <algorithm>
```

## 函数原型:

```cpp
template< class BidirIt >
constexpr void reverse( BidirIt first, BidirIt last );
```

## 作用
将序列 [`first`, `last`) 的元素在原容器中颠倒重排

## 函数实现
```c++
template<class BidirIt>
void reverse(BidirIt first, BidirIt last)
{
    while ((first != last) && (first != --last)) {
        std::iter_swap(first++, last);
    }
}

template<typename RandomAccessIterator>
    void reverse(RandomAccessIterator first, RandomAccessIterator Last,){
      ... ...
      while (__first < __last){
	  std::iter_swap(__first, __last);
          ++__first;
	  --__last;
      }
}
```

## Example
  
```cpp
#include <iostream>     // std::cout
#include <algorithm>    
#include <vector>       // std::vector

int main () {
    std::vector<int> v{1,2,3};
    std::reverse(std::begin(v), std::end(v));
    for(auto e : v) std::cout << e << ' ';
    std::cout << '\n';
 
    int a[] = {4, 5, 6, 7};
    std::reverse(std::begin(a), std::end(a));
    for(auto e : a) std::cout << e << ' ';
    return 0;
}
```
**[See Example](snippets/reverse.cpp)**    

**[Run Code](https://rextester.com/JPEG65734)**