# itoa

## 头文件
```cpp
#include <numeric>
```

## 函数原型:

```cpp
template< class ForwardIt, class T >
constexpr void iota( ForwardIt first, ForwardIt last, T value );
```

## 作用
在某区间 [first, last) 填入某指定值 value 的递增序列。 

 ```cpp
template<class ForwardIt, class T>
constexpr // since C++20
void iota(ForwardIt first, ForwardIt last, T value)
{
    while(first != last) {
        *first++ = value;
        ++value;
    }
}
 ```


## Example
  
 ```cpp
int main()
{
    int arr[10];
    //Initialising the starting value as 500
    int num = 500;
    //Applying the function iota to each element
    std::iota(arr, arr + 10, num);
    // Printing the final output
    for(int i = 0; i < 10; i++)
    	cout<< arr[i] <<" ";
    return 0;
}
 ```
