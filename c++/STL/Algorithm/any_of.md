# any_of

## 头文件
```cpp
#include <algorithm>
```

## 函数原型:

```cpp
template< class InputIt, class UnaryPredicate >
constexpr bool any_of( InputIt first, InputIt last, UnaryPredicate p );

```

## 作用
 检查区间 [fast, last) 中是否有一个元素满足函数p
```cpp
template< class InputIt, class UnaryPredicate >
constexpr bool any_of(InputIt first, InputIt last, UnaryPredicate p)
{
    return std::find_if(first, last, p) != last;
}
```
 
  ## Example
```cpp
int main() {
    
    std::vector<int> v{1, 3, 5, 7, 2};
	
	if (std::any_of(v.begin(), v.end(), [](int i){ return i % 2 == 0; }))	{ 
		std::cout << "A number is even\n"; 
	}
    else{
        std::cout << "No number is even\n";
    }
} 
```
  
