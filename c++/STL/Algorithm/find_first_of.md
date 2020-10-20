# find

## 头文件
```cpp
#include <algorithm>  
```

## 函数原型:

```cpp
template< class InputIt, class ForwardIt >
constexpr InputIt find_first_of( InputIt first, InputIt last,
                                 ForwardIt s_first, ForwardIt s_last );

// 函数重载,使用自定义的函数方法p
template< class InputIt, class ForwardIt, class BinaryPredicate >
constexpr InputIt find_first_of( InputIt first, InputIt last,
                                 ForwardIt s_first, ForwardIt s_last, BinaryPredicate p );
```

## 作用
 以 [first, last) 区间内的某些元素作为查找目标，寻找在 [s_first, s_last) 区间内的第一次出现地点。 
 
 ```cpp
template<class InputIt, class ForwardIt>
InputIt find_first_of(InputIt first, InputIt last,
                      ForwardIt s_first, ForwardIt s_last)
{
    for (; first != last; ++first) {
        for (ForwardIt it = s_first; it != s_last; ++it) {
            if (*first == *it) {
                return first;
            }
        }
    }
    return last;
}

// 函数重载
template<class InputIt, class ForwardIt, class BinaryPredicate>
InputIt find_first_of(InputIt first, InputIt last,
                      ForwardIt s_first, ForwardIt s_last,
                      BinaryPredicate p)
{
    for (; first != last; ++first) {
        for (ForwardIt it = s_first; it != s_last; ++it) {
            if (p(*first, *it)) {
                return first;
            }
        }
    }
    return last;
}
 ```


  ## Example
  
 ```cpp
int main()
{
    std::vector<int> v{0, 2, 3, 25, 5};
    std::vector<int> t{3, 19, 10, 2};
 
    auto result = std::find_first_of(v.begin(), v.end(), t.begin(), t.end());
 
    if (result == v.end()) {
        std::cout << "no elements of v were equal to 3, 19, 10 or 2\n";
    } else {
        std::cout << "found a match at "
                  << std::distance(v.begin(), result) << "\n";
    }
    // output : found a match at 1
    return 0;
}
 ```
