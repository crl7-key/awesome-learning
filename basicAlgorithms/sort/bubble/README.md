# bubble-sort

冒泡排序是一种最基础的交换排序。

交换排序:两两比较待排序的关键字，并交换不满足次序要求的那对数，直到整个表都满足次序要求为止。

例如：冒泡排序原理：
- 比较相邻的元素。如果第一个比第二个大，就交换他们两个。
```c++
for(int i = 1; i < len; i++) {
    if(arr[i-1] > arr[i]) { // 第一个比第二个大
        swap(arr[i-1],arr[i]); // 交换两元素位置
    }
}
```
- 对每一对相邻元素做同样的工作，从开始第一对到结尾的最后一对。在这一点，最后的元素应该会是最大的数。
- 针对所有的元素重复以上的步骤，除了最后一个。
- 持续每次对越来越少的元素重复上面的步骤，直到没有任何一对数字需要比较。


冒泡排序的时间复杂度为![](https://latex.codecogs.com/gif.latex?O（n^2）) ，并且是一种稳定的排序。
## 基础版本
```c++
template<class T>
void bubbleSort(T arr[],int len) {
    for(int i = 0; i < len - 1; i++) { // 比较的轮数
        for(int j = 0; j <len - i - 1; j++) { // 比较的次数 len - i -1 
            if (arr[j] > arr[j+1]) { // 第一个比第二个大
                int tmp = arr[j+1];
                arr[j+1] = arr[j];
                arr[j] = tmp;
            }
        }
    }
}
```

## 优化版本
```c++
template<class T>
void bubbleSort(T arr[],int len) {
    bool swaped;
    do
    {
        swaped = false;
        for(int i = 1; i < len; i++) {
            if(arr[i-1] > arr[i]) {
                swap(arr[i-1],arr[i]);
                swaped = true;
            }
        }
    }while(swaped);
}
```


