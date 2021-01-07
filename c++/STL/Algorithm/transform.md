# transform

## 头文件
```cpp
#include  <algorithm>
```

## 函数原型:

```cpp
template< class InputIt, class OutputIt, class UnaryOperation >
constexpr OutputIt transform( InputIt first1, InputIt last1, OutputIt d_first,
                              UnaryOperation unary_op );


// 函数重载，使用自定义二分查找函数
template< class InputIt1, class InputIt2, class OutputIt, class BinaryOperation >
constexpr OutputIt transform( InputIt1 first1, InputIt1 last1, InputIt2 first2,
                              OutputIt d_first, BinaryOperation binary_op );
```


## 作用
`std::transform` 应用给定的函数到范围并存储结果于始于`d_first`的另一范围。以两个序列为基础，交互作用产生第三个序列,执行结果放进迭代器 result 所标示的容器中。

## 函数实现
```cpp
template<class InputIt, class OutputIt, class UnaryOperation>
OutputIt transform(InputIt first1, InputIt last1, OutputIt d_first, 
                   UnaryOperation unary_op)
{
    while (first1 != last1) {
        *d_first++ = unary_op(*first1++);
    }
    return d_first;
}


// 函数重载

template<class InputIt1, class InputIt2, 
         class OutputIt, class BinaryOperation>
OutputIt transform(InputIt1 first1, InputIt1 last1, InputIt2 first2, 
                   OutputIt d_first, BinaryOperation binary_op)
{
    while (first1 != last1) {
        *d_first++ = binary_op(*first1++, *first2++);
    }
    return d_first;
}
```

## Example
  
```cpp
#include <iostream>
#include <algorithm>
#include <functional>

int main()
{
    int arr1[] = {1, 2, 3}; // Creating array of size 3
    int arr2[] = {4, 5, 6}; // Creating array of size 3
    int n = sizeof(arr1)/sizeof(arr1[0]); 
    int res[n]; 
  
    /*
    Applies op to each of the elements and stores the value returned by each operation in the range that begins at result.
    */
    std::transform(arr1, arr1+n, arr2, res, std::plus<int>()); 
    
    // print result
    for (int i=0; i<n; i++) 
        std::cout << res[i] << " "; 
    
    return 0;
}
```
**[See Example](snippets/transform.cpp)**    

**[Run Code](https://rextester.com/GDKM38867)**