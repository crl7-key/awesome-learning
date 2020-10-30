#ifndef INC_INSERTION_SORT_GENERATE_TEST_CASES_SORTTESTHLPER_H_
#define INC_INSERTION_SORT_GENERATE_TEST_CASES_SORTTESTHLPER_H_

#include <iostream>
#include <ctime>
#include <cassert>
#include <string>

using namespace std;

namespace SortTestHelper
{
    // 无序生成n个元素的随机数组，每个元素的随机范围为(rangL,rangR)
    template<typename T>
    T * generateRandomArray(int n,int rangL,int rangR) {
        assert(rangL <= rangR);
        //在堆区申请空间
        T *arr = new int[n];

        srand(time(NULL));
        for(int i = 0;i < n;i++)
            arr[i] = rand()%(rangR - rangL +1) + rangL;
            return arr;        
    }
    //有序生成n个元素的随机数组
    template<class T>
    T *generateNeralyOrdereArray(int n,int swapTimes) {
        T *arr = new T[n];
        for(int i = 0;i<n;i++)
            arr[i] = i;

        srand(time(NULL));
        for(int i = 0;i < swapTimes;i++) {
            int posx = rand() % n;
            int posy = rand() % n;

            swap(arr[posx],arr[posy]);
        }
        return arr;
    }

    // 打印数组
    template<typename T>
    void print_array(T arr[],int n) {
        for(int i = 0;i < n;i++)
            cout << arr[i] << " ";
        cout<<endl;
    }

    // 判断是否排序成功
    template<typename T>
    bool isSorted(T arr[],int n) {
        for(int i = 0;i < n-1;i++)
            if(arr[i] > arr[i+1])
                return false;
        return true;
    }

    // 测试算法所用时间
    template<typename T>
    void testSort(const string &sortName,void(*sort)(T[],int n),T arr[],int n) {
        clock_t startTime = clock();
        sort(arr,n);
        clock_t endTime = clock();
        
        assert(isSorted(arr,n));
        
        cout << sortName << " :" << double(endTime - startTime)/CLOCKS_PER_SEC <<" s" << endl;
        return;
        
    }
    // 拷贝数组模板
    template<class T>
    T* copyArray(T arr[],int n) {
        T* newArr = new T[n];
        copy(arr,arr+n,newArr);
        return newArr;
    }
}
#endif // INC_INSERTION_SORT_GENERATE_TEST_CASES_SORTTESTHLPER_H_