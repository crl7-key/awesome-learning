## std::list<T,Allocator>::end

作用：
返回指向`list`末元素后一元素的迭代器。

此元素表现为占位符；试图访问它导致未定义行为

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

    std::list<int>::iterator it = mylist.end(); 
    
    std::cout << "Returned iterator points to : " << *it << std::endl;   
   
    std::cout << "mylist contains: ";
    for (auto it = mylist.begin();it != mylist.end(); it++) { 
        std::cout << *it << " "; 
    } 
    return 0;
}
```

**[Run Code](https://rextester.com/YCB75419)**