## std::list<T,Allocator>::erase

作用：
用于从列表容器中删除元素。此函数可用于从指定的列表容器中删除单个元素或一系列元素。


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
    return 0;
}
```

**[Run Code](https://rextester.com/QFHW41075)**