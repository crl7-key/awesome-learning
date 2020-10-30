#ifndef INC_SHELL_SORT_H_
#define INC_SHELL_SORT_H_

template<class T>
void shellSort(T arr[],int len ) {
    int h = 1;
    while(h < len/3 )
        // 计算步长的增量并按步长分组
        h = 3 * h + 1;

    while(h >= 1) {
        for( int i = h; i < len; i++ ) {
            //对 arr[i],arr[i-h],arr[i-2*h],arr[i-3*h]使用插入算法
            T tmp = arr[i];
            int j;
            for ( j = i; j >= h && tmp < arr[j-h];j -= h )
                arr[j] = arr[j-h];
            arr[j] = tmp;
        }
        h /= 3;
    }
}
#endif // !INC_SHELL_SORT_H_