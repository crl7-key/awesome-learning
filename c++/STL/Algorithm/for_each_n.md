# for_each_n

## 头文件
```cpp
#include <algorithm>  
```

## 函数原型:

```cpp
template< class InputIt, class Size, class UnaryFunction >
constexpr InputIt for_each_n( InputIt first, Size n, UnaryFunction f );
```

## 作用
将仿函数 f 应用于 [first, last) 区间内的n个元素。 

 ```cpp
template<class InputIt, class Size, class UnaryFunction>
InputIt for_each_n(InputIt first, Size n, UnaryFunction f)
{
    for (Size i = 0; i < n; ++first, (void) ++i) {
        f(*first);
    }
    return first;
}
 ```


## Example
  
 ```cpp
class Display {
public: 
    void operator() (int i) { 
    std::cout << i << " ";
    }
};

int main()
{
    std::vector<int> a{3,2,3,9};
      // Applying the function object Display to each element of a 
    std::for_each_n(a.begin(), 2, Display()); // Will output, "3 2 "
    return 0;
}
 ```
