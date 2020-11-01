#ifndef INC_HEAP_SORT_H_
#define INC_HEAP_SORT_H_

#include "max_heap_basic.h"

template<typename T>
void __heapSort(T arr[],int n) {
    MaxHeap<T> maxheap = MaxHeap<T>(arr,n);
    for(int i = n-1; i >= 0 ;i--)
        arr[i] = maxheap.extractMax();
}

template<class T>
void heapSort(T arr[],int n) {
    MaxHeap<T> maxheap = MaxHeap<T>(n);

    for(int i = 0;i < n;i++)
        maxheap.insert(arr[i]);

    for(int i =  n-1;i >= 0;i--)
        arr[i] = maxheap.extractMax();
}
#endif // !INC_HEAP_SORT_H_