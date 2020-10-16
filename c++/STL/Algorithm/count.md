# count

## 头文件
```cpp
#include <algorithm>  
```


## 函数原型:

```cpp
template< class InputIt, class T >
constexpr typename iterator_traits<InputIt>::difference_type
              count( InputIt first, InputIt last, const T &value );
```

## 作用
 将 [first, last) 区间内的每一个元素拿来和指定值 value 比较,并返回与 value 相等的元素个数。
 
 ```cpp
template<class InputIt, class T>
typename iterator_traits<InputIt>::difference_type
    count(InputIt first, InputIt last, const T& value)
{
    typename iterator_traits<InputIt>::difference_type ret = 0;
    for (; first != last; ++first) {
        if (*first == value) {
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
    int target  = 3;
    int num = std::count(v.begin(), v.end(), target);
    
    std::cout << "number: " << target << " count: " << num << '\n';
    
    // output : number: 3 count: 2
}
 ```
