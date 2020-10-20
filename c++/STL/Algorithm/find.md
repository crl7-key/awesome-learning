# find

## 头文件
```cpp
#include <algorithm>  
```

## 函数原型:

```cpp
template< class InputIt, class T >
constexpr InputIt find( InputIt first, InputIt last, const T& value );
```

## 作用
 循环查找 [first, last) 内的所有元素，找出第一个匹配条件的，返回指向该元素的迭代器。 
 
 ```cpp
template<class InputIt, class T>
constexpr InputIt find(InputIt first, InputIt last, const T& value)
{
    for (; first != last; ++first) {
        if (*first == value) {
            return first;
        }
    }
    return last;
}
 ```


  ## Example
  
 ```cpp
int main()
{
    std::vector<int> v{ 1, 2, 3, 4, 4, 3, 7, 8, 9, 10 };

    int searchme = 4;
    if(std::find(std::begin(v), std::end(v), searchme) != std::end(v)){
        std::cout <<"\n v contains 4";
    }
    else
        std::cout<<"No match !!";

    // output : v contains 4
    return 0;
}
 ```
