# fill_n

## 头文件
```cpp
#include <algorithm>  
```

## 函数原型:

```cpp
template< class OutputIt, class Size, class T >
constexpr OutputIt fill_n( OutputIt first, Size count, const T& value );
```

## 作用
 将范围（即向量）中的多个元素设置为一个值。 该函数接受3个参数。 范围的迭代器，从迭代器的第一个元素开始设置的元素数和新值。
 
 ```cpp
template<class OutputIt, class Size, class T>
OutputIt fill_n(OutputIt first, Size count, const T& value)
{
    for (Size i = 0; i < count; i++) {
        *first++ = value;
    }
    return first;
}
 ```


  ## Example
  
 ```cpp
void print_vector(const std::vector<int> &v) {
    // iterate through v and print its elements
    for(auto &elem:v) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

int main()
{
    std::vector<int> v = {1,1,1,1,1,1,1,1};

    std::cout << "Before fill_n: ";
    print_vector(v);
    // output : Before fill_n: 1 1 1 1 1 1 1 1 
    

    // set the first half of v's elements to zero
    std::fill_n(v.begin(), v.size()/2, 0);

    std::cout << "After  fill_n: ";
    print_vector(v);
    //output : After  fill_n: 0 0 0 0 1 1 1 1 
    return 0;
}
 ```
