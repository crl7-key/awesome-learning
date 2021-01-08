# std::list<T,Allocator>::cbegin

作用：

返回指向`list`首元素的迭代器。

若`list`为空，则返回的迭代器将等于`end()`。


Example:
```cpp
#include <iostream>
#include <list>

int main()
{
    // declaration of list 
    std::list<int> lis = { 15, 26, 37, 48, 59 }; 
  
    // Prints the first element 
    std::cout << "The first element is: " << *lis.cbegin(); 
  
    // printing list elements 
    std::cout << "\nList: "; 
  
    for (auto it = lis.cbegin(); it != lis.end(); ++it) 
        std::cout << *it << " "; 
    return 0;
}
```

**[Run Code](https://rextester.com/TNV89592)**