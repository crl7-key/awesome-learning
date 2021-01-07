# std::list<T,Allocator>::back


作用：
返回到容器中最后一个元素的引用。在空容器上调用`back`导致未定义行为。


Example:

```c++
#include <iostream>
#include <list>
 
int main()
{
    // Initialization of list 
    std::list<int> demo_list; 
  
    // Adding elements to the list 
    demo_list.push_back(10); 
    demo_list.push_back(20); 
    demo_list.push_back(30); 
  
    // prints the last element of demo_list 
    std::cout << demo_list.back(); 
    return 0;
}
```
**[Run Code](https://rextester.com/ZFEBH76608)**