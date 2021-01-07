# unique

## 头文件
```cpp
#include  <algorithm>
```

## 函数原型:

```cpp
template< class ForwardIt >
constexpr ForwardIt unique( ForwardIt first, ForwardIt last );


// 函数重载
template< class ForwardIt, class BinaryPredicate >
constexpr ForwardIt unique( ForwardIt first, ForwardIt last, BinaryPredicate p );
```


## 作用
如果冗余数据位于任何数据结构的连续地址中，则使用“唯一”来删除这些数据。它不会删除数据，只是将其替换为其他元素。它不会影响数据结构的大小,能够移除重复的元素。每当在 [`first`, `last`) 内遇到重复元素群，它便移除该元素群中第一个以后的所有元素。

## 可能的实现
```cpp
template<class ForwardIt>
ForwardIt unique(ForwardIt first, ForwardIt last)
{
    if (first == last)
        return last;
 
    ForwardIt result = first;
    while (++first != last) {
        if (!(*result == *first) && ++result != first) {
            *result = std::move(*first);
        }
    }
    return ++result;
}

// 函数重载
template<class ForwardIt, class BinaryPredicate>
ForwardIt unique(ForwardIt first, ForwardIt last, BinaryPredicate p)
{
    if (first == last)
        return last;
 
    ForwardIt result = first;
    while (++first != last) {
        if (!p(*result, *first) && ++result != first) {
            *result = std::move(*first);
        }
    }
    return ++result;
}
```

## Example
  
```cpp
#include <iostream>
#include <algorithm>
#include <vector>


int main()
{
    std::vector<int> vec = {1,1,3,3,5,5,5,1,2,2,8,9,9,9,0,8};
		
    std::vector<int>::iterator it;
    it = std::unique(vec.begin(),vec.end());
		
    vec.resize(std::distance(vec.begin(),it));
		
    // output : 1 3 5 1 2 8 9 0 8
    for(it = vec.begin();it != vec.end();++it) {
        std::cout<<" "<<*it;
    }
}
```
**[See Example](snippets/unique.cpp)**    

**[Run Code](https://rextester.com/WNJWNV45018)**