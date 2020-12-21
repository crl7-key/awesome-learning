# partition

## 头文件
```cpp
#include  <algorithm>
```

## 函数原型:

```cpp
template< class ForwardIt, class UnaryPredicate >
constexpr ForwardIt partition( ForwardIt first, ForwardIt last, UnaryPredicate p );
```

## 作用
此函数用于根据参数中提到的条件对元素进行分区, 将区间 [`first`, `last`) 中的元素重新排列。所有被一元条件运算`pred` 判定为`true`的元素，都会被放在区间的前段，被判定为`false`的元素，都会被放在区间的后段。



## 函数实现
```c++
template<class ForwardIt, class UnaryPredicate>
ForwardIt partition(ForwardIt first, ForwardIt last, UnaryPredicate p)
{
    first = std::find_if_not(first, last, p);
    if (first == last) return first;
 
    for (ForwardIt i = std::next(first); i != last; ++i) {
        if (p(*i)) {
            std::iter_swap(i, first);
            ++first;
        }
    }
    return first;
}
```

## Example
  
 ```cpp
#include <algorithm> 
#include <iostream> 
#include <vector>

int main() {
    
    std::vector<int> my_vector = { 2, 1, 5, 6, 8, 7 };

    // Partitioning my_vector in basis of even numbers condition
    std::partition(my_vector.begin(), my_vector.end(), [](int x){ 
        return x%2==0; 
    });
    
    // Verifying if my_vector is partitioned
    if ( std::is_partitioned(my_vector.begin(), my_vector.end(), [](int x){ return x%2==0; } )) {
        std::cout << "The vector is partitioned!\n" << std::endl;
    } else{
        std::cout << "The vector is not partitioned!\n" << std::endl;
    }
    
    // output: 2 8 6 5 1 7
    for (auto n : my_vector)
        std::cout << n << ' ';
    std::cout << '\n'; 
    
    return 0;
} 
 ```
**[See Example](snippets/partition.cpp)**    

**[Run Code](https://rextester.com/AGMM7684)**