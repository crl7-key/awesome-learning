# pop_heap

## 头文件
```cpp
#include  <algorithm>
```

## 函数原型:

```cpp
template< class BidirIt >
constexpr bool prev_permutation( BidirIt first, BidirIt last);

// 函数重载
template< class BidirIt, class Compare >
constexpr bool prev_permutation( BidirIt first, BidirIt last, Compare comp);
```

## 作用
它用于将[`first`，`last`）范围内的元素重新排列为先前的“按字典顺序较小”的排列。如果函数可以将对象重新排列为字典顺序较小的排列，则返回“`true`”。否则，它返回“`false`”。

## 函数实现
```c++
template<class BidirIt>
bool prev_permutation(BidirIt first, BidirIt last)
{
    if (first == last) return false;
    BidirIt i = last;
    if (first == --i) return false;
 
    while (1) {
        BidirIt i1, i2;
 
        i1 = i;
        if (*i1 < *--i) {
            i2 = last;
            while (!(*--i2 < *i))
                ;
            std::iter_swap(i, i2);
            std::reverse(i1, last);
            return true;
        }
        if (i == first) {
            std::reverse(first, last);
            return false;
        }
    }
}
```

## Example
  
 ```cpp
#include <algorithm> 
#include <iostream> 

int main() {
    
    int arr[] = {1,2,3};

    std::sort (arr,arr+3);
    std::reverse (arr,arr+3);

    std::cout << "The 3! possible permutations with 3 elements:\n";
    do {
      std::cout << arr[0] << ' ' << arr[1] << ' ' << arr[2] << '\n';
    } while ( std::prev_permutation(arr,arr+3) );

    std::cout << "After loop: " << arr[0] << ' ' << arr[1] << ' ' << arr[2] << '\n';

    return 0;
} 
 ```
**[See Example](snippets/prev_permutations.cpp)**    

**[Run Code](https://rextester.com/RPVR26568)**