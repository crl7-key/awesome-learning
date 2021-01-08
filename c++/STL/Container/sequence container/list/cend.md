# std::list<T,Allocator>::cend

作用：
返回指向`list`末元素**后一元素**的迭代器。

此元素表现为占位符；试图访问它导致未定义行为。

Example:
```cpp
#include <iostream>
#include <list>

int main()
{
    // declaration of list 
    std::list<int> lis = { 100, 200, 300, 400, 500 }; 
  
    // printing list elements 
    std::cout << "List: " << std::endl; 
  
    for (auto it = lis.cbegin(); it != lis.cend(); ++it) 
        std::cout << *it << " "; 
    return 0;
}
```

**[Run Code](https://rextester.com/VYY19703)**