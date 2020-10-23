# is_permutation

## 头文件
```cpp
#include <algorithm>
```

## 函数原型:

```cpp
template< class ForwardIt1, class ForwardIt2 >
constexpr bool is_permutation( ForwardIt1 first1, ForwardIt1 last1,
                               ForwardIt2 first2 );

// 函数重载
template< class ForwardIt1, class ForwardIt2 >
constexpr bool is_permutation( ForwardIt1 first1, ForwardIt1 last1,
                               ForwardIt2 first2, ForwardIt2 last2 );

// 重载函数,使用自定义的函数方法p
template< class ForwardIt1, class ForwardIt2, class BinaryPredicate >
constexpr bool is_permutation( ForwardIt1 first1, ForwardIt1 last1,
                               ForwardIt2 first2, ForwardIt2 last2,
                               BinaryPredicate p );
```

## 作用
比较两个容器中的元素,如果发现两个容器中的所有元素都匹配,则返回`true`,即使以不同顺序返回,否则返回`false`。 第一个范围从[first1,last1）开始,第二个范围从`first2`开始。

```cpp
template<class ForwardIt1, class ForwardIt2>
bool is_permutation(ForwardIt1 first, ForwardIt1 last,
                    ForwardIt2 d_first)
{
    // skip common prefix
    std::tie(first, d_first) = std::mismatch(first, last, d_first);
    // iterate over the rest, counting how many times each element
    // from [first, last) appears in [d_first, d_last)
    if (first != last) {
        ForwardIt2 d_last = std::next(d_first, std::distance(first, last));
        for (ForwardIt1 i = first; i != last; ++i) {
            if (i != std::find(first, i, *i)) continue; // this *i has been checked
 
            auto m = std::count(d_first, d_last, *i);
            if (m==0 || std::count(i, last, *i) != m) {
                return false;
            }
        }
    }
    return true;
}
```


## Example
  
 ```cpp
template<typename Os, typename V>
Os& operator<< (Os& os, V const& v) {
    os << "{ ";
    for (auto const& e : v) os << e << ' ';
    return os << "}";
}
 
int main()
{
    static constexpr auto v1 = {1,2,3,4,5};
    static constexpr auto v2 = {3,5,4,1,2};
    static constexpr auto v3 = {3,5,4,1,1};
 
    std::cout << v2 << " is a permutation of " << v1 << ": " << std::boolalpha
              << std::is_permutation(v1.begin(), v1.end(), v2.begin()) << '\n'
              // output : { 3 5 4 1 2 } is a permutation of { 1 2 3 4 5 }: true
              << v3 << " is a permutation of " << v1 << ": " << std::boolalpha
              << std::is_permutation(v1.begin(), v1.end(), v3.begin()) << '\n';
              // output : { 3 5 4 1 1 } is a permutation of { 1 2 3 4 5 }: false

    return 0;
}
 ```
