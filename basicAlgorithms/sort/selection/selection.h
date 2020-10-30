#ifndef INC_INSERTION_SORT_H_
#define INC_INSERTION_SORT_H_


template<class T>
void Swap(T& a , T& b)
{
    T temp;
    temp = a;
    a = b;
    b = temp;
}

template<class T>
void selectionSort(T arr[],int len) {
    for(int i = 0;i < len;i++ ) {
        // 寻找[i,leng]中区间的最小值
        int minIndex = i;
        for(int j = i;j < len;j++)
            if (arr[j] < arr[minIndex])
                minIndex = j;

        // swap(arr[i],arr[minIndex]);
        swap(arr[i],arr[minIndex]);
    }
}
#endif // !INC_INSERTION_SORT_H_
