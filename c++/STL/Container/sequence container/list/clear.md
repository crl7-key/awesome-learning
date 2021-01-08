# std::list<T,Allocator>::clear

作用：
从容器擦除所有元素。此调用后`size()`返回零。

非法化任何指代所含元素的引用、指针或迭代器。任何尾后迭代器保持合法。


## Example:
```cpp
#include <iostream>
#include <list>

int main()
{
    std::list<int> mylist{ 1, 2, 3, 4, 5 }; 
  
    mylist.clear(); 
    // List becomes empty 
  
    // Printing the list 
    for (auto value : mylist) {
        std::cout << ' ' << value;  
    }
    std::cout << "end" << std::endl;
    return 0;
}
```

**[Run Code](https://rextester.com/VUBNR48802)**