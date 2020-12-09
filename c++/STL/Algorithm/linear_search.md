# linear_search

线性搜索用于从数组的左到右查找术语，并尝试查找存在的元素（如果存在）返回其索引，由于其他搜索算法（例如二进制搜索算法和哈希表）与线性搜索相比，搜索速度显着提高，因此很少使用


```cpp
#include <iostream>

int linear_search(int arr[], int n, int x) {
        int i;
    for (i = 0; i < n; i++)
        if (arr[i] == x)
            return i;
    return -1;
}

int main()

{

    int arr[] = { 2, 3, 4, 10, 40 };

    int x = 10;

    int n = sizeof(arr) / sizeof(arr[0]);

    int result = linear_search(arr, n, x);

    if (result == -1){
        std::cout<<"Element is not present in array";
    }
    else{
        std::cout<<"Element is present at index " << result << std::endl;                                                                     
    }
   return 0;

}
```
**[Run Code](https://rextester.com/BFFCB16982)**
