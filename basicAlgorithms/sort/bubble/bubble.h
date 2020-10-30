#ifndef INC_BUBBLE_SORT_H_
#define INC_BUBBLE_SORT_H_

#include <iostream>
#include <algorithm>

using namespace std;

template<class T>
void bubbleSort1(T arr[],int len) {
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

template<class T>
void bubbleSort(T arr[],int len) {
    bool swaped ;
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

#endif // !INC_BUBBLE_SORT_H_
