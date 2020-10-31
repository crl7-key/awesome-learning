#ifndef INC_OPTIMIZATION_H_
#define INC_OPTIMIZATION_H_

#include "debug.h"
#include <algorithm>
#include <ctime>
#include <cstdlib> // srand

// 对arr[left...right]范围的数组进行插入排序
template<typename T>
void insertionSort(T arr[] ,int left, int right) {
    for(int i = left + 1;i <= right;i++) {
        T temp = arr[i];
        int j;
        for(j = i;j > 0 && arr[j-1] > temp;j--)
            arr[j] = arr[j-1];
        arr[j] = temp;
    }
    return;
}

// 返回base,使得arr[left...base-1] < arr[base] <  arr[index+1...right];
template<class T>
int partition(T arr[],int left,int right) {

    std::swap(arr[left],arr[rand()%(right - left + 1) + left]);
    T v = arr[left];
    // arr[left+1...j] < v  < arr[j+1...i) ,  j为分割点
    int j = left;   
    for(int i = left +1;i <= right;i++) {
        if(arr[i] < v){
            j++;
            std::swap(arr[j],arr[i]);
        }
    }
    std::swap(arr[left],arr[j]);
    return j;
}

//对arr[left...right]部分进行快速排序
template<class T>
void quickSort(T arr[],int left,int right) {
    if ( right - left <= 15 ) { // 对区间元素数量小于15的使用插入排序
        insertionSort(arr,left,right);
        return;
    }

    int base = partition(arr,left,right);  // 分割点，找基准数据的正确索引
    output(left,base,right,arr);
    quickSort(arr,left,base -1);           // 对 < base的部分进行快速排序
    quickSort(arr,base+1,right);           // 对 > base的部分进行快速排序

}


template<class T>
void quick(T arr[],int n) {
    std::srand(time(NULL));
    quickSort(arr,0,n-1);
}
#endif // !INC_OPTIMIZATION_H_