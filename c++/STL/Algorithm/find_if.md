# find_if

## 头文件
```cpp
#include <algorithm>  
```

## 函数原型:

```cpp
template< class InputIt, class UnaryPredicate >
constexpr InputIt find_if( InputIt first, InputIt last,
                           UnaryPredicate p );
```

## 作用
根据指定的`p`运算条件，循环查找 [first, last) 内的所有元素，找出第一个令`p`运算结果为`true`，返回指向该元素的迭代器。   

 ```cpp
template<class InputIt, class UnaryPredicate>
constexpr InputIt find_if(InputIt first, InputIt last, UnaryPredicate p)
{
    for (; first != last; ++first) {
        if (p(*first)) {
            return first;
        }
    }
    return last;
}
 ```


## Example
  
 ```cpp
bool IsOdd (int i) {
    return ((i%2)==1);
}

int main()
{
    std::vector<int> v{ 1, 2, 3, 4, 4, 3, 7, 8, 9, 10 };
    if(std::find_if(std::begin(v), std::end(v), IsOdd) != std::end(v)) {
        std::cout <<"\n Odd Value Found";
    }
    else
        std::cout<<"No match !!";
    // output: OddValue Found
    return 0;
}
 ```
