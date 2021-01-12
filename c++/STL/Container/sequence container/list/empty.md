## std::list<T,Allocator>::empty

作用：
用于检查特定列表容器是否为空。即是否 `begin()` == `end()` 。

## Example
```cpp
#include <iostream>
#include <list>

int main()
{
    std::list<int> mylist;
    if (mylist.empty()) {
        std::cout << "mylist is empty"<< std::endl;
    } else {
        std::cout << "not empty" << std::endl;;
    }
    
    mylist.emplace_back(1);
    mylist.emplace_back(2);
    mylist.emplace_back(3);

    if (mylist.empty()) {
        std::cout << "mylist is empty"<< std::endl;
    } else {
        std::cout << "not empty" << std::endl;;
    }
    
    std::cout << "mylist contains: ";
    for (auto& value: mylist)
        std::cout << value << " ";
    return 0;
}
```

**[Run Code](https://rextester.com/ZWOMOZ20329)**