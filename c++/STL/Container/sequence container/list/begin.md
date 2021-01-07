## std::list<T,Allocator>::begin

作用：
返回指向`list`首元素的迭代器。

若`list`为空，则返回的迭代器将等于`end()`。

## Example

```cpp
#include <iostream>
#include <list>
 
int main()
{
    // declaration of list container 
    std::list<int> mylist{ 1, 2, 3, 4, 5 }; 
  
    // using begin() to print list 
    for (auto it = mylist.begin(); it != mylist.end(); ++it) 
        std::cout << ' ' << *it;  // output : 1,2,3,4,5
    return 0;
}
```
**[Run Code](https://rextester.com/CFGKI13221)**