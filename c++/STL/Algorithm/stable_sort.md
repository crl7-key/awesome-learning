# stable_sort

## 头文件
```cpp
#include  <algorithm>
```

## 函数原型:

```cpp
template< class RandomIt >
void stable_sort( RandomIt first, RandomIt last );

// 函数重载，使用自定义的函数comp
template< class RandomIt, class Compare >
void stable_sort( RandomIt first, RandomIt last, Compare comp );
```


## 作用
该函数对数组进行排序。`stable_sort`对元素进行排序，以保持其顺序，就像原始数组的离线排序一样。

## Example
  
```cpp
#include <iostream>
#include <algorithm>

  
int main() {
    //sample array
    int arr[] = {1,1,3,5,4,9,4};
    //sorting the array
    std::stable_sort(arr,arr + 7);
    //array after sorting
    for(int i = 0;i < 7;i++){
        std::cout << arr[i] << " ";
    }
    //outputs 1 1 3 4 4 5 9
    return 0;
} 

```
**[See Example](snippets/stable_sort.cpp)**    

**[Run Code](https://rextester.com/OFNQH14990)**