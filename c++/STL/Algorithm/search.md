# search

## 头文件
```cpp
#include  <algorithm>
```

## 函数原型:

```cpp
template< class ForwardIt1, class ForwardIt2 >
constexpr ForwardIt1 search( ForwardIt1 first, ForwardIt1 last,
                             ForwardIt2 s_first, ForwardIt2 s_last );

// 函数重载
template< class ForwardIt1, class ForwardIt2, class BinaryPredicate >
constexpr ForwardIt1 search( ForwardIt1 first, ForwardIt1 last,
                             ForwardIt2 s_first, ForwardIt2 s_last, BinaryPredicate p );              

template<class ForwardIt, class Searcher>
constexpr ForwardIt search( ForwardIt first, ForwardIt last,
                            const Searcher& searcher );                                            
```

## 作用
在序列一 [`first1`, `last1`) 所涵盖的区间中，查找序列二 [`first2`, `last2`) 的首次出现点。

## 函数实现
```c++
template<class ForwardIt1, class ForwardIt2>
ForwardIt1 search(ForwardIt1 first, ForwardIt1 last,
                        ForwardIt2 s_first, ForwardIt2 s_last)
{
    for (; ; ++first) {
        ForwardIt1 it = first;
        for (ForwardIt2 s_it = s_first; ; ++it, ++s_it) {
            if (s_it == s_last) {
                return first;
            }
            if (it == last) {
                return last;
            }
            if (!(*it == *s_it)) {
                break;
            }
        }
    }
}

// 函数重载，使用自定义的函数p
template<class ForwardIt1, class ForwardIt2, class BinaryPredicate>
ForwardIt1 search(ForwardIt1 first, ForwardIt1 last,
                        ForwardIt2 s_first, ForwardIt2 s_last, 
                        BinaryPredicate p)
{
    for (; ; ++first) {
        ForwardIt1 it = first;
        for (ForwardIt2 s_it = s_first; ; ++it, ++s_it) {
            if (s_it == s_last) {
                return first;
            }
            if (it == last) {
                return last;
            }
            if (!p(*it, *s_it)) {
                break;
            }
        }
    }
}
```

## Example
  
```cpp
#include <vector>
#include <iostream>
#include <algorithm>
 
int main()
{
   std::vector<int> vec {10, 20, 30, 40, 50, 60, 70, 80, 90};
   int arr[] = {40,50,60,70};
    
   std::vector<int>::iterator it;
    
   it = std::search (vec.begin(), vec.end(), arr, arr + 4);
    
   if (it != vec.end()){
     std::cout << "arr found at position " << (it - vec.begin()) << '\n';
   }
   else{
     std::cout << "arr not found\n";
   }
    
    return 0;
}
```
**[See Example](snippets/search.cpp)**    

**[Run Code](https://rextester.com/IAFWL9594)**