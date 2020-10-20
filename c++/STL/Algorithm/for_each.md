# for_each

## 头文件
```cpp
#include <algorithm>  
```

## 函数原型:

```cpp
template< class InputIt, class UnaryFunction >
constexpr UnaryFunction for_each( InputIt first, InputIt last, UnaryFunction f );
```

## 作用
将仿函数 f 应用于 [first, last) 区间内的每一个元素上。 

 ```cpp
template<class InputIt, class UnaryFunction>
constexpr UnaryFunction for_each(InputIt first, InputIt last, UnaryFunction f)
{
    for (; first != last; ++first) {
        f(*first);
    }
    return f; // implicit move since C++11
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
    std::for_each(a.begin(), a.end(), Display()); // Will output: 3 2 3 9
    return 0;
}
 ```
