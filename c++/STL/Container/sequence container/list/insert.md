## std::list<T,Allocator>::insert

作用：
用于在列表的任何位置插入元素,插入是指 插入在...之前，插入完成后，新节点将位于标示出插入点所指之节点的前方。

## Example
```cpp
#include <iostream>
#include <list>

int main()
{
    // declaring list 
    std::list<int> mylist; 
  
    // using assign() to insert multiple numbers 
    // creates 3 occurrences of "2" 
    mylist.assign(3, 2); 
    
    // initializing list iterator to beginning 
    std::list<int>::iterator it = mylist.begin(); 
  
    // iterator to point to 3rd position 
    advance(it, 2); 
    
    for (auto value : mylist) {
        std::cout << value << " "; 
    }
    std::cout << std::endl;
    // using insert to insert 1 element at the 3rd position 
    // inserts 5 at 3rd position 
    mylist.insert(it, 5); 
    
    // Printing the new list 
    std::cout << "The list after inserting" << " 1 element using insert() is : "; 
    for (auto value : mylist) {
        std::cout << value << " "; 
    }
  
    std::cout << std::endl; 
    return 0;
}
```

**[Run Code](https://rextester.com/KDLYI88249)**
