#ifndef INC_QUICK_THREE_WAY_H_
#define INC_QUICK_THREE_WAY_H_

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

/*
 三路快速排序处理arr[left...right]
将arr[left...right]分为 < v; == v; > v三部分区域
之后递归对 < v 和 > v 两部分区域继续进行三路快速排序
 */
template<class T>
void quickSort3Ways(T arr[],int left,int right) {
    if (right - left <= 15) { // 对区间元素数量小于15的使用插入排序
        insertionSort(arr,left,right);
        return;
    }
    // partition
    // 随机化找到一个元素作为"基准"元素 
    std::swap(arr[left],arr[rand()%(right - left + 1) + left]);
    T v = arr[left];

    int less_t = left;          // arr[left+1...less_t] < v 起始位置
    int greater_t = right + 1;  // arr[greater_t...right] > v 起始位置
    int i = left + 1;           // arr[left+1...i) == v   起始位置

    while(i < greater_t){
        if (arr[i] < v) {      // 当前位置元素 < v，将当前位置元素与 < v 区域的第一个元素交换位置 
            std::swap(arr[i],arr[less_t + 1]);
            i++;
            less_t++;
        }
        else if (arr[i] > v) { // 当前位置元素 > v，将当前位置元素与 > v 区域的第一个元素的前一个元素交换位置
            std::swap(arr[i],arr[greater_t - 1]);
            greater_t--;
        }
        else { // arr[i] == v
            i ++;
        }
    }

    std::swap(arr[left],arr[less_t]);            // 遍历完成,将整个序列的第一个元素放到合适的位置

    quickSort3Ways(arr,left,less_t-1);    // 对 < v 区域递归调用三路排序
    quickSort3Ways(arr,greater_t,right);  // 对 > v 区域递归调用三路排序

}


template<class T>
void quick(T arr[],int n) {
    std::srand(std::time(NULL));
    quickSort3Ways(arr,0,n-1);
}
#endif // !INC_QUICK_THREE_WAY_H_