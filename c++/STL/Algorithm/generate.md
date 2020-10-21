
# generate

## 头文件
```cpp
#include  <numeric>  
```

## 函数原型:

```cpp
template< class ForwardIt, class Generator >
constexpr void generate( ForwardIt first, ForwardIt last, Generator g );
```

## 作用
 将仿函数 g 的运算结果赋值给 [first, last) 区间内的所有元素上
 ```cpp
template<class ForwardIt, class Generator>
void generate(ForwardIt first, ForwardIt last, Generator g)
{
    while (first != last) {
        *first++ = g();
    }
}
 ```


  ## Example
  
 ```cpp
int foo() { 
        static int i = 0; 
        return ++i; 
    }

int main()
{
    int i; 
    std::vector<int> v(10); 
  
    std::generate(v.begin(), v.end(), foo); 
  
    for (auto value : v) {
        std::cout << value << " ";
    }
    std::cout << "\n";
    // output: 0 ,1 ,2 ,3 ,4 ,5 , 6, 7, 8, 9

    std::generate(v.begin(), v.end(), [n = 0] () mutable { return n++; });
 
    std::cout << "v: ";
    for (auto iv: v) {
        std::cout << iv << " ";
    }
    std::cout << "\n";
    // output : v: 0 1 2 3 4 5 6 7 8 9
    return 0;
}
 ```
