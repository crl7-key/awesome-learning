## std::list<T,Allocator>::max_size

作用：
返回根据系统或库实现限制的容器可保有的元素最大数量，即对于最大容器的 std::distance(begin(), end()) 。

## Example
```cpp
#include <iostream>
#include <list>
 
int main()
{
    std::list<int> mylist;
    // checking the max size of the list 
    std::cout << "Maximum size of a 'list' is " << mylist.max_size() << "\n";
    // output : Maximum size of a 'list' is 768614336404564650
}
```

**[Run Code](https://rextester.com/JTH94395)**
