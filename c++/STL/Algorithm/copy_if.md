
# copy_if

## 头文件
```cpp
#include <algorithm>  
```

## 函数原型:

```cpp
template< class InputIt, class OutputIt, class UnaryPredicate >
constexpr OutputIt copy_if( InputIt first, InputIt last,
                            OutputIt d_first,
                            UnaryPredicate pred );
```

## 作用
 将[first,last）如果值满足特定条件,则将[first,last）定义的范围内的元素复制到另一个从传递的参数开始的范围内,即复制范围的某些元素,第四个参数为自定义一元函数满足特定条件。  
 ```cpp
template<class InputIt, class OutputIt, class UnaryPredicate>
OutputIt copy_if(InputIt first, InputIt last, 
                 OutputIt d_first, UnaryPredicate pred)
{
    while (first != last) {
        if (pred(*first))
            *d_first++ = *first;
        first++;
    }
    return d_first;
}
 ```


  ## Example
  
 ```cpp
int main()
{
    auto fn = [](int i) {
        return ((i%2) == 1);
    };

    std::vector<int> vec {1, 2, 3};
    std::vector<int> res;

    // Will copy from vec [begin, end), to res
    std::copy_if(vec.begin(), vec.end(), std::back_inserter(res), fn);
    
    // res is now {1, 3}
    for (auto value : res) { 
        std::cout << value << " "; 
    }
}
 ```
