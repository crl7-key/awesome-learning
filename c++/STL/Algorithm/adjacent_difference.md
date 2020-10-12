# adjacent_difference

## 头文件
```cpp
#include  <numeric>  
```

## 函数原型:

```cpp
template< class InputIt, class OutputIt >
constexpr OutputIt adjacent_difference( InputIt first, InputIt last,
                                        OutputIt d_first );

template< class InputIt, class OutputIt, class BinaryOperation >
constexpr OutputIt adjacent_difference( InputIt first, InputIt last,
                                        OutputIt d_first, BinaryOperation op );
```

## 作用
 第一个原型用来计算 [first, last) 中相邻元素的差值, 并写入它们到始于 d_first + 1 的范围
 ```cpp
template<class InputIt, class OutputIt>
constexpr // since C++20
OutputIt adjacent_difference(InputIt first, InputIt last, 
                             OutputIt d_first)
{
    if (first == last) return d_first;
 
    typedef typename std::iterator_traits<InputIt>::value_type value_t;
    value_t acc = *first;
    *d_first = acc;
    while (++first != last) {
        value_t val = *first;
        *++d_first = val - std::move(acc); // std::move since C++20
        acc = std::move(val);
    }
    return ++d_first;
}
 ```
 第二个原型相当于函数重载,最后一个参数是为改变相邻元素差值运算而加载的二元函数,就是让二元函数取代默认的相邻元素差值运算,即可以自定义回调函数。
```cpp
template<class InputIt, class T, class BinaryOperation>
constexpr // since C++20
T accumulate(InputIt first, InputIt last, T init, 
             BinaryOperation op)
{
    for (; first != last; ++first) {
        init = op(std::move(init), *first); // std::move since C++20
    }
    return init;
}
```

  ## Example
  ```cpp
int main()
{
   std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
   std::adjacent_difference(v.begin(), v.end(), v.begin());  // 计算 v[first, last) 中相邻元素的差值
   
   for (auto n : v)
        std::cout << n << ' ';
        
   std::cout << '\n';
   // ouput :   1 1 1 1 1 1 1 1 1 1
   
   std::vector<int> res(v.size(),0);
   std::adjacent_difference(v.begin(), v.end(), res.begin(),  std::plus<> {});  // std::plus<>{} defined in header <functional>
   for (auto n : res)
        std::cout << n << ' ';
        
   std::cout << '\n';
   // output  : 1 2 2 2 2 2 2 2 2 2
   return 0;
}
  
  ```
  
