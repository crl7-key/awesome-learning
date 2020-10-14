
# copy_if

## 头文件
```cpp
#include <algorithm>  
```

## 函数原型:

```cpp
template< class InputIt, class Size, class OutputIt >
constexpr OutputIt copy_n( InputIt first, Size count, OutputIt result );
```

## 作用
 将从第一个开始的范围中的前n个元素复制到result开始的范围  
 
 ```cpp
template< class InputIt, class Size, class OutputIt>
OutputIt copy_n(InputIt first, Size count, OutputIt result)
{
    if (count > 0) {
        *result++ = *first;
        for (Size i = 1; i < count; ++i) {
            *result++ = *++first;
        }
    }
    return result;
}
 ```


  ## Example
  
 ```cpp
int main()
{
    std::vector<int> vec {1, 2, 3};
    std::vector<int> res;

    // Will copy 2 values starting at vec.begin, to res
    std::copy_n(vec.begin(), 2, std::back_inserter(res));
    
    // res is now {1, 2}
    for (auto value : res) { 
        std::cout << value << " "; 
    }
}
 ```
