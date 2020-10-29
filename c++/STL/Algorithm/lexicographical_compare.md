# lexicographical_compare

## 头文件
```cpp
#include <algorithm>
```

## 函数原型:

```cpp
template< class InputIt1, class InputIt2 >
constexpr bool lexicographical_compare( InputIt1 first1, InputIt1 last1,
                                        InputIt2 first2, InputIt2 last2 );

// 函数重载
template< class InputIt1, class InputIt2, class Compare >
constexpr bool lexicographical_compare( InputIt1 first1, InputIt1 last1,
                                        InputIt2 first2, InputIt2 last2,
                                        Compare comp );                                        
```

## 作用
以 "字典排列方式" 对两个序列 [first1, last1) 和 [first2, last2) 进行比较。

 ```cpp
template<class InputIt1, class InputIt2>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                             InputIt2 first2, InputIt2 last2)
{
    for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
        if (*first1 < *first2) return true;
        if (*first2 < *first1) return false;
    }
    return (first1 == last1) && (first2 != last2);
}

// 函数重载,使用自定义的函数方法 comp
template<class InputIt1, class InputIt2, class Compare>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                             InputIt2 first2, InputIt2 last2,
                             Compare comp)
{
    for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
        if (comp(*first1, *first2)) return true;
        if (comp(*first2, *first1)) return false;
    }
    return (first1 == last1) && (first2 != last2);
}
 ```


## Example
  
 ```cpp
int main()
{
    std::string a[] = {"dog", "cat", "cow"};
        
    std::string b[] = {"dog","pigglet","cow"};
      
    if( std::lexicographical_compare(a,a+1,b,b+1)) { 
        std::cout << "True";          
    } 
    else {         
        std::cout << "False";           
    } 
    // output :: False
    return 0;
}
 ```
