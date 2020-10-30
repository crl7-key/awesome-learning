#include "selection.h"

#include "SortTestHelper.h"

int main(int argc, char const *argv[])
{
    int len = 1000;
    // 随机数组 
    cout << "Test for Random Array,size = " << len << " ,random range [0," << len << "]" <<endl;
    int* arr = SortTestHelper::generateRandomArray<int>(len,0,len);

    SortTestHelper::testSort("Selection Sort",selectionSort,arr,len);

    delete []arr;

    // 有序数组测试
    cout << "Test for NeralyOrdere ,size = " << len << " ,NeralyOrder range [0," << len << "]" <<endl;
    int* arr2 = SortTestHelper::generateNeralyOrdereArray<int>(len,len);
    SortTestHelper::testSort("Selection Sort",selectionSort,arr2,len);

    delete []arr2;
    return 0;
}
