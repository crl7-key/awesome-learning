#include "HeapSort.h"
#include "SortTestHelper.h"

#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
   int n = 100000;
    // 一般性测试,随机数组生成
    cout << "Test for Random Array, size = " << n << ", random range [0, " << n << "]" << endl;
    int* arr = SortTestHelper::generateRandomArray<int>(n,0,n);
    int* arr2 = SortTestHelper::copyArray<int>(arr,n);

    SortTestHelper::testSort("Heap Sort 1",heapSort,arr,n);
    SortTestHelper::testSort("Heap Sort 2",__heapSort,arr2,n);

    delete [] arr;
    delete [] arr2;

    // 测试近乎有序的数组
    int swap_time = 100;
    cout << "Test for Random Nearly Ordered Array, size = " << n << ", swap time = " << swap_time << endl;
    
    arr = SortTestHelper::generateNeralyOrdereArray<int>(n,swap_time);
    arr2 = SortTestHelper::copyArray<int>(arr,n);

    delete [] arr;
    delete [] arr2;

    SortTestHelper::testSort("Heap Sort 1",heapSort,arr,n);
    SortTestHelper::testSort("Heap Sort 2",__heapSort,arr2,n);

    // 测试存在大量相同元素的数组
    cout << "Test for Random Array, size = " << n << ", random range [0, 10]" << endl;
    arr = SortTestHelper::generateRandomArray<int>(n,0,10);
    arr2 = SortTestHelper::copyArray<int>(arr,n);

    SortTestHelper::testSort("Heap Sort 1",heapSort,arr,n);
    SortTestHelper::testSort("Heap Sort 2",__heapSort,arr2,n);

    delete [] arr;
    delete [] arr2;

    cout << endl;

    return 0;
}
