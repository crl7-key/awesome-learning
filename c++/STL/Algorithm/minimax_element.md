# minmax_element

## 头文件
```cpp
#include  <algorithm>
```

## 函数原型:

```cpp
template< class ForwardIt >
constexpr std::pair<ForwardIt,ForwardIt>
    minmax_element( ForwardIt first, ForwardIt last );

// 函数重载
template< class ForwardIt, class Compare >
constexpr std::pair<ForwardIt,ForwardIt>
    minmax_element( ForwardIt first, ForwardIt last, Compare comp );
```

## 作用
此函数返回一个带有迭代器的对，该迭代器指向在[`first`，`last`）范围内最小值的元素作为第一个元素，而最大的作为第二个元素。寻找范围 [`first`, `last`) 中最小和最大的元素。

```cpp
template<class ForwardIt>
std::pair<ForwardIt, ForwardIt> 
    minmax_element(ForwardIt first, ForwardIt last)
{
    using value_type = typename std::iterator_traits<ForwardIt>::value_type;
    return std::minmax_element(first, last, std::less<value_type>());
}
// 函数重载，使用自定义的comp函数
template<class ForwardIt, class Compare>
std::pair<ForwardIt, ForwardIt> 
    minmax_element(ForwardIt first, ForwardIt last, Compare comp)
{
    auto min = first, max = first;
 
    if (first == last || ++first == last)
        return {min, max};
 
    if (comp(*first, *min)) {
        min = first;
    } else {
        max = first;
    }
 
    while (++first != last) {
        auto i = first;
        if (++first == last) {
            if (comp(*i, *min)) min = i;
            else if (!(comp(*i, *max))) max = i;
            break;
        } else {
            if (comp(*first, *i)) {
                if (comp(*first, *min)) min = first;
                if (!(comp(*i, *max))) max = i;
            } else {
                if (comp(*i, *min)) min = i;
                if (!(comp(*first, *max))) max = first;
            }
        }
    }
    return {min, max};
}
```

## Example
  
 ```cpp
#include <iostream>
#include <algorithm>
#include <array>

int main()
{
    std::array<int,7> foo {3,7,2,9,5,8,6};  // 3,7,2,9,5,8,6

    //  在[first，last）范围内的最小值作为第一个元素，而最大值作为第二个元素
    auto result = std::minmax_element (foo.begin(),foo.end());

    std::cout << "min is " << *result.first; 
    std::cout << ", at position " << (result.first-foo.begin()) << std::endl;
    std::cout << "max is " << *result.second;
    std::cout << ", at position " << (result.second-foo.begin()) << std::endl;
    
    return 0;
}
 ```

**[Run Code](https://rextester.com/WKUO85915)**