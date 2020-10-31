#ifndef INC_QUICK_BASE_H_
#define INC_QUICK_BASE_H_

#include "debug.h"

template<class T>
int partition(T arr[],int left,int right) {
    // 以最左边的数(left)为基准
    int base = arr[left];
    while (left < right) {
        // 从序列右端开始,向左遍历,直到找到小于base的数
        while (left < right && arr[right] >= base)
            right--;
        // 找到了比base小的元素,将这个元素放到最左边的位置
        arr[left] = arr[right];
 
        // 从序列左端开始,向右遍历,直到找到大于base的数
        while (left < right && arr[left] <= base)
            left++;
        // 找到了比base大的元素,将这个元素放到最右边的位置
        arr[right] = arr[left];
    }
 
    // 最后将base放到left位置。此时,left位置的左侧数值应该都比left小；
    // 而left位置的右侧数值应该都比left大。
    arr[left] = base;
    return left;
}


template<class T>
void quickSort(T arr[],int left,int right) {
    if (left < right) {  // 左下标一定小于右下标，否则就会越界
        // 对数组进行分割，取出下次分割的基准标号
        int base = partition(arr, left, right);
        output(left,base,right,arr);
        // 对“基准标号“左侧的一组数值进行递归的切割，以至于将这些数值完整的排序
        quickSort(arr,left,base - 1);

        // 对“基准标号“右侧的一组数值进行递归的切割，以至于将这些数值完整的排序
        quickSort(arr,base + 1,right);
    }
}


template<class T>
void quick(T arr[],int n) {
    quickSort(arr,0,n-1);
}

#endif // !INC_QUICK_BASE_H_