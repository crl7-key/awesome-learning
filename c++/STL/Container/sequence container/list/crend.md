## std::list<T,Allocator>::rend

作用：
返回指向逆向`list`末元素后一元素的逆向迭代器。它对应非逆向`list`首元素的前一元素。此元素表现为占位符，试图访问它导致未定义行为。

## Example
```cpp
#include <iostream>
#include <list>

int main()
{
    // declaration of the list 
    std::list<int> lis = { 27, 46, 65, 84, 30, 22 }; 
  
    std::cout << "List: " << std::endl; 
  
    for (auto it = lis.crbegin(); it != lis.crend(); ++it) 
        std::cout << *it << " "; 
    return 0;
}
```

**[Run Code](https://rextester.com/SGTW14542)**