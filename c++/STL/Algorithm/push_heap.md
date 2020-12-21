# push_heap

## 头文件
```cpp
#include  <algorithm>
```

## 函数原型:

```cpp
template< class RandomIt >
constexpr void push_heap( RandomIt first, RandomIt last );

// 函数重载
template< class RandomIt, class Compare >
constexpr void push_heap( RandomIt first, RandomIt last,
                          Compare comp );
```

## 作用
给定一个堆在[`first`，`last-1`）范围内，此函数通过将（`last-1`）中的值放到[`first`，`last-1`）中相应的位置，将范围扩展到[`first`，`last-1`）


## Example
  
 ```cpp
#include <iostream>     // std::cout
#include <algorithm>    // std::make_heap, std::pop_heap, std::push_heap, std::sort_heap
#include <vector>       // std::vector

int main () {
    int arr[] = {10,20,30,5,15};
    std::vector<int> v(arr,arr+5);

    std::make_heap (v.begin(),v.end());
    std::cout << "initial max heap   : " << v.front() << '\n';

    std::pop_heap (v.begin(),v.end()); v.pop_back();
    std::cout << "max heap after pop : " << v.front() << '\n';

    v.push_back(99); 
    std::push_heap (v.begin(),v.end());
    std::cout << "max heap after push: " << v.front() << '\n';

    std::sort_heap (v.begin(),v.end());

    std::cout << "final sorted range :";
    for (unsigned i=0; i<v.size(); i++)
      std::cout << ' ' << v[i];

    std::cout << '\n';

    return 0;
}
 ```
**[See Example](snippets/push_heap.cpp)**    

**[Run Code](https://rextester.com/NDP25626)**