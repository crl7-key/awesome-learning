#ifndef INC_QUICK_SELECT_H
#define INC_QUICK_SELECT_H

#include <algorithm>
#include "debug.h"
//返回index,使得arr[left...index-1] < arr[index] < arr[index+1...right];
template<class T>
int partition(T arr[],int left,int right) {
    // 以首个元素(最左边的数)作为基准
    T v = arr[left];
    // arr[left+1...j] < v ; arr[j+1...i) > v, j为分割点
    int j = left;   
    for(int i = left +1;i <= right;i++) { // 当arr[i] > v ;i++ ,arr[i] < v; j++ 
        if(arr[i] < v) {
            j++;
            std::swap(arr[j],arr[i]);
        }
    }
    std::swap(arr[left],arr[j]);
    return j;
}

//对arr[left...right]部分进行快速排序,查找排名为 k 的元素
template<class T>
int quickSort(T arr[],int left,int right,int k) {
    if (left >= right)
        return arr[left];
    
    int base = partition(arr,left,right); // 分割点,寻找基准数据的正确索引
    output(left,base,right,arr);

    int index = base - left + 1;
    if (index == k) return arr[base];
    if (index > k) return quickSort(arr,left,base - 1,k);   // 如果 index > k，在前半部分查找排名第 k 位的元素
    return quickSort(arr,base + 1, right, k - index);       // 如果 index < k, 在后半部分查找排名第 k - index 位的元素
}

template<class T>
int quick(T arr[],int n,int k) {
    return quickSort(arr,0,n-1,k);
}
#endif // !INC_QUICK_SELECT_H
