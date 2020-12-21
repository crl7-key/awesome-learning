# move

## 头文件
```cpp
#include  <algorithm>
```

## 函数原型:

```cpp
template< class T >
constexpr std::remove_reference_t<T>&& move( T&& t ) noexcept;
```

## 作用
将一个左值强制转化为右值引用，继而可以通过右值引用使用该值，以用于移动语义。从实现上讲，`std::move`基本等同于一个类型转换：`static_cast<T&&>(lvalue)`;


## Example
  
 ```cpp
#include <iostream>     
#include <algorithm>    
#include <vector>       

int main () {
    
    std::string str1 = "Hello";             
    std::string str2 = "Word";             

    std::vector<std::string> avector;

    avector.push_back (str1);               // copies the first string
    avector.push_back (std::move(str2));    // moves the second string

    std::cout << "Printing the vector: ";
    for (std::string& x:avector) {
        std::cout << ' ' << x;  
    } 
    std::cout << '\n';

    std::cout << "First string after copy: "
              << str1 << std::endl;
    std::cout << "Second string after move: "
              << str2 << std::endl;

    return 0;
}
 ```

**[Run Code](https://rextester.com/NBQC82301)**