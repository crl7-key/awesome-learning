
# accumulate

## 头文件
```cpp
#include  <numeric>  
```

## 函数原型:

```cpp
template< class InputIt, class T >
T accumulate( InputIt first, InputIt last, T init );

template< class InputIt, class T, class BinaryOperation >
T accumulate( InputIt first, InputIt last, T init,
              BinaryOperation op );
```

## 作用
 第一个原型用来计算给定值init和范围内元素的总和[first, last)  
 ```cpp
 template<class InputIt, class T>
constexpr // since C++20
T accumulate(InputIt first, InputIt last, T init)
{
    for (; first != last; ++first) {
        init = std::move(init) + *first; // std::move since C++20
    }
    return init;
}
 ```
 第二个原型相当于函数重载,最后一个参数是为改变求和运算而加载的二元函数,就是让二元函数取代默认的求和运算.
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
    int sum = std::accumulate(v.begin(), v.end(), 0);   // 计算 0 和 v[first,last) 内所有元素的总和
    std::cout << "sum: " << sum << std::endl;           // ouput :   sum : 55
    
    // 自定义的回调函数
    auto dash_fold = [](std::string a, int b) {
                         return std::move(a) + '-' + std::to_string(b);
                     };
                     
    std::string str = std::accumulate(std::next(v.begin()), v.end(),
                                    std::to_string(v[0]), // start with first element
                                    dash_fold);   
    
    std::cout << "dash-separated string: " << str << std::endl; // output :  dash-separated string: 1-2-3-4-5-6-7-8-9-10 
 
    return 0;
}
 ```
