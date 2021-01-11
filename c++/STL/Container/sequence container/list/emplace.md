## std::list<T,Allocator>::emplace

作用：
此功能用于通过在给定位置插入新元素来扩展列表

## Example
```cpp
#include <iostream>
#include <list>

int main()
{
    // declaration of list 
    std::list< std::pair<int,char> > mylist;
    
    // using emplace() function to
    // insert new element at the
    // beginning of the list
    mylist.emplace ( mylist.begin(), 100, 'x' );
    mylist.emplace ( mylist.begin(), 200, 'y' );
    
    // printing the list
    // after inserting the value
    // at the beginning
    std::cout << "mylist contains:";
    for (auto& x: mylist)
       std::cout << " (" << x.first << "," << x.second << ")";

    std::cout << '\n';
}
```