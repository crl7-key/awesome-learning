#include "quick_select.h"
#include "SortTestHelper.h"

int main(int argc, char const *argv[])
{
    int len = 30;
    // 随机数组 
    cout << "Test for Random Array,size = " << len << " ,random range [0," << len << "]" <<endl;
    int* arr = SortTestHelper::generateRandomArray<int>(len,0,len);


    for (int i = 1; i <= len; i++) {
        std:: cout << "排名第" << i << "位的元素：" << quick<int>(arr,len,i) << std::endl;
    }

    delete []arr;
    
    return 0;
}
