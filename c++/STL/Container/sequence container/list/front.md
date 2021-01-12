## std::list<T,Allocator>::front

作用：
返回到容器首元素的引用。

在空容器上对`front`的调用是未定义的。

## Example
```cpp
#include <iostream>
#include <list>

int main()
{
    std::list<int> mylist;
    
    mylist.push_back(1);
    mylist.push_back(2);
    mylist.push_back(3);
    
    std::cout << "Printing elements of list before deleting  mylist contains: ";
    for (auto it = mylist.begin();it != mylist.end(); it++) { 
        std::cout << *it << " "; 
    } 
    std::cout << "\n";
    std::list<int>::iterator it = mylist.begin(); 
    
    std::cout << "Returned iterator points to : " << *it << std::endl;   
   
    mylist.erase(it);
    std::cout << "Printing elements of list after deleting  mylist contains: ";
    for (auto it = mylist.begin();it != mylist.end(); it++) { 
        std::cout << *it << " "; 
    } 
    std::cout << "\n";
    auto e = mylist.front();
    std::cout << e << std::endl;
    return 0;
}
```

**[Run Code](https://rextester.com/ZHX99086)**