## std::list<T,Allocator>::merge

作用：
归并二个已排序链表为一个。链表应以升序排序。

## Example
```cpp
#include <iostream>
#include <list>
 
int main()
{
    // declaring the lists 
    // initially sorted 
    std::list<int> list1 = { 10, 20, 30 }; 
    std::list<int> list2 = { 40, 50, 60 }; 
  
    // merge operation 
    list2.merge(list1); 
  
    std::cout << "List:  "; 
    for (auto value : list2) {
        std::cout << value << " "; 
    }
    return 0;
}
```

**[Run Code](https://rextester.com/OEEUZ32078)**
