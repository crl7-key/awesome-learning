# std::list<T,Allocator>::assign

作用：
替换容器的内容。用于将值分配给列表。

example：

```cpp
#include <iostream>
#include <list>

int main(int argc, const char** argv) 
{
    // Initialization of list 
    std::list<int> demo_list;

    // Assigning the value 100, 5 times to the list, list_demo.
    demo_list.assign(5,100);

    // Displaying the list 
    for (int it : demo_list) {
        std::cout << it << std::endl;
    }

    return 0;
}
```    

**[Run Code](https://rextester.com/ZSB5314)**
