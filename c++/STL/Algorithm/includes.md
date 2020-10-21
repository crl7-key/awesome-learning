# includes

## 头文件
```cpp
#include <algorithm>  
```

## 函数原型:

```cpp
template< class InputIt1, class InputIt2 >
constexpr bool includes( InputIt1 first1, InputIt1 last1,
                         InputIt2 first2, InputIt2 last2 );

// 函数重载
template< class InputIt1, class InputIt2, class Compare >
constexpr bool includes( InputIt1 first1, InputIt1 last1,
                         InputIt2 first2, InputIt2 last2, Compare comp );
```

## 作用
    判断排序范围[first1，last1）是否包含（包括）另一个排序范围[first2，last2）中的所有元素。
 
 ```cpp
template<class InputIt1, class InputIt2>
bool includes(InputIt1 first1, InputIt1 last1,
              InputIt2 first2, InputIt2 last2)
{
    for (; first2 != last2; ++first1)
    {
        if (first1 == last1 || *first2 < *first1)
            return false;
        if ( !(*first1 < *first2) )
            ++first2;
    }
    return true;
}

// 函数重载,使用自定义的函数方法comp
template<class InputIt1, class InputIt2, class Compare>
bool includes(InputIt1 first1, InputIt1 last1,
              InputIt2 first2, InputIt2 last2, Compare comp)
{
    for (; first2 != last2; ++first1)
    {
        if (first1 == last1 || comp(*first2, *first1))
            return false;
        if (!comp(*first1, *first2))
            ++first2;
    }
    return true;
}
 ```


  ## Example
  
 ```cpp
template<class Os, class Co> Os& operator<<(Os& os, const Co& v) {
  for (auto i : v) os << i << ' ';
  return os << '\t';
}

int main()
{
   const auto
    v1 = {'a', 'b', 'c', 'f', 'h', 'x'},
    v2 = {'a', 'b', 'c'},
    v3 = {'a', 'c'},
    v4 = {'a', 'a', 'b'},
    v5 = {'g'},
    v6 = {'a', 'c', 'g'},
    v7 = {'A', 'B', 'C'};
 
  auto no_case = [](char a, char b) { return std::tolower(a) < std::tolower(b); };

  // output: a b c f h x 
  std::cout
    << v1 << "\nincludes:\n" << std::boolalpha
    << v2 << ": " << std::includes(v1.begin(), v1.end(), v2.begin(), v2.end()) << '\n'   // a b c   : true
    << v3 << ": " << std::includes(v1.begin(), v1.end(), v3.begin(), v3.end()) << '\n'   // a c     : true
    << v4 << ": " << std::includes(v1.begin(), v1.end(), v4.begin(), v4.end()) << '\n'   // a a b   : false
    << v5 << ": " << std::includes(v1.begin(), v1.end(), v5.begin(), v5.end()) << '\n'   // g       : false
    << v6 << ": " << std::includes(v1.begin(), v1.end(), v6.begin(), v6.end()) << '\n'   // a c g   : false
    << v7 << ": " << std::includes(v1.begin(), v1.end(), v7.begin(), v7.end(), no_case)  // A B C   : true 
          << " (case-insensitive)\n";

    return 0;
}
 ```
