## std::list<T,Allocator>::crbegin


作用：
返回指向逆向`list`首元素的逆向迭代器。它对应非逆向`list`的末元素。若`list`为空，则返回的迭代器等于`rend()`。


## Example
```cpp
#include <iostream>
#include <list>

int main()
{
   // declaration of the list 
    std::list<int> lis = { 109, 207, 305, 403, 501 }; 
  
    // prints the last element 
    std::cout << "The last element is: " << *lis.crbegin(); 
    std::cout << "\nList: "; 
  
    for (auto it = lis.crbegin(); it != lis.crend(); ++it) 
        std::cout << *it << " "; 
    return 0;
}
```
**[Run Code](https://rextester.com/OZZ45038)**
