
# count_if

## 头文件
```cpp
#include <algorithm>  
```

## 函数原型:

```cpp
template< class InputIt, class UnaryPredicate >
constexpr typename iterator_traits<InputIt>::difference_type
              count_if( InputIt first, InputIt last, UnaryPredicate p );
```

## 作用
 返回满足特定条件的[first,last）范围内的元素数(计算等于value的元素)。  
 
 ```cpp
template<class InputIt, class UnaryPredicate>
typename iterator_traits<InputIt>::difference_type
    count_if(InputIt first, InputIt last, UnaryPredicate p)
{
    typename iterator_traits<InputIt>::difference_type ret = 0;
    for (; first != last; ++first) {
        if (p(*first)) {
            ret++;
        }
    }
    return ret;
}
 ```


  ## Example
  
 ```cpp
int main()
{
    std::vector<int> v{ 1, 2, 3, 4, 4, 3, 7, 8, 9, 10 };
 
    // use a lambda expression to count elements divisible by 3.
    int num = std::count_if(v.begin(), v.end(), [](int i){return i % 3 == 0;});
    
    std::cout << "number divisible by three: " << num << '\n';
    
    // output : number divisible by three: 3
}
 ```
