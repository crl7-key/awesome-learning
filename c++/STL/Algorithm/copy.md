# copy

## 头文件
```cpp
#include  <numeric>  
```

## 函数原型:

```cpp
template< class InputIt, class OutputIt >
constexpr OutputIt copy( InputIt first, InputIt last, OutputIt d_first );

```

## 作用
 将输入区间 [first, last) 内的元素复制到输出区间 [result, result + (last-first)) 内。
 ```cpp
template<class InputIt, class OutputIt>
OutputIt copy(InputIt first, InputIt last, 
              OutputIt d_first)
{
    while (first != last) {
        *d_first++ = *first++;
    }
    return d_first;
}
 ```

  ## Example
  ```cpp
int main()
{
   std::vector<int> vec {1, 2, 3};
   std::vector<int> res;
   
   std::copy(vec.begin(), vec.end(), std::back_inserter(res));
   
   for (auto n : res)
        std::cout << n << ' ';
   
   std::cout << '\n';
   // output : res is now {1, 2, 3}
        
   return 0;
}
  
  ```
  
