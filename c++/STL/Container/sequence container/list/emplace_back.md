## std::list<T,Allocator>::emplace_back

作用：
用于将元素添加到列表的末尾

## Example
```cpp
#include <iostream>
#include <list>

int main()
{
   std::list<int> mylist;

    mylist.emplace_back(1);
    mylist.emplace_back(2);
    mylist.emplace_back(3);

    std::cout << "mylist contains: ";
    for (auto& x: mylist)
        std::cout << x << " ";
    return 0;
}
```

**[Run Code](https://rextester.com/VLYQAF78812)**