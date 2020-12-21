# none_of

## 头文件
```cpp
#include  <algorithm>
```

## 函数原型:

```cpp
template< class InputIt, class UnaryPredicate >
constexpr bool none_of(InputIt first, InputIt last, UnaryPredicate p);
```

## 作用
此函数对数组元素的整个范围进行操作，并检查每个元素上的给定属性，并且当范围中的任何元素都不满足指定属性时返回`true`，否则返回`false`

## 函数原型
```c++
template< class InputIt, class UnaryPredicate >
bool none_of(InputIt first, InputIt last, UnaryPredicate p)
{
    return std::find_if(first, last, p) == last;
}
```

## Example
  
 ```cpp
#include <vector> 
#include <algorithm> 
#include <iostream> 


int main() {
    
    std::vector<int> v{1, 3, 5, 7};
	
    if (std::none_of(v.begin(), v.end(), [](int i){ return i % 2 == 0; })) { 
        std::cout << "No number is  even\n"; 
    }
    else {
        std::cout << "A number is even\n";
    }
}
 ```

**[Run Code](https://rextester.com/WOXT97798)**