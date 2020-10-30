#ifndef INC_INSERTION_H_
#define INC_INSERTION_H_

template<class T>
void insertionSort(T arr[],int len) {
    // 第1个数肯定是有序的,从第2个数开始遍历,依次插入有序序列
    for(int i = 1;i < len;i++) {
        // 取出第i个数,和前i-1个数比较后,插入合适位置
        T tmp = arr[i];
        int j;
        for( j = i;j > 0 && arr[j-1] > tmp;j--)
            arr[j] = arr[j-1];
        arr[j] = tmp;
    }
}

#endif // !INC_INSERTION_H_
