# selection_sort

选择排序：每趟从待排序的记录中选出关键字最小的记录，顺序放在已排序的记录序列末尾，直到全部排序结束为止


选择排序原理：
- 在未排序序列中找到最小（大）元素,存放到排序序列的起始位置
- 从剩余未排序元素中继续寻找最小（大）元素,然后放到已排序序列的末尾,即将其和第一个元素互换
- 重复第二步,以此类推,直到所有元素均排序完毕

```c++
template<class T>
void selectionSort(T arr[],int len) {
    for(int i = 0;i < len;i++ ) {
        // 寻找[i,leng]中区间的最小值
        int minIndex = i;
        for(int j = i;j < len;j++)
            if (arr[j] < arr[minIndex])
                minIndex = j;

        // 将找到的第i个小的数值放在第i个位置上
        swap(arr[i],arr[minIndex]);
    }
}
```