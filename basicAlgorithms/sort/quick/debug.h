#ifndef INC_DEBUG_H_
#define INC_DEBUG_H_

#include <iostream>
// DEBUG = 0 关闭调试信息 1 开启调试信息
#define DEBUG 1

int n = 10;

template<class T>
void output(int left, int base, int right, T arr[]) {
    if (!DEBUG) return ;
    std::cout << "待排序区间范围 [ "<< left <<" ," << right  << "]"  << std::endl;
    
    std::cout << "基准值： " << arr[base] << std::endl;
    char str[30];
    int cnt = 1;
    for (int i = 1; i < base; i++) {
        cnt += sprintf(str, "%d ", arr[i]);
    }
    for (int i = 1; i < left; i++) printf("%d ", arr[i]);
    std::cout << "[ ";
    for (int i = left; i <= right; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "]";
    for (int i = right + 1; i <= n; i++) std::cout << arr[i];
    std::cout << std::endl;
    for (int i = 0; i < cnt; i++) std::cout << " ";
    std::cout << "^" << std::endl;
    for (int i = 0; i < cnt; i++) std::cout << " ";
    std::cout << "|" << std::endl;
    std::cout << std::endl;
    std::cout << "按回车继续" << std::endl;
    while (getchar() != '\n') ;
    return ;
}


template<class T>
void read_data(T arr[]) {
    std::cout << "请输入元素数量" << std::endl;
    scanf("%d", &n);
    std::cout << "请输入 "<< n <<" 个整数" << std::endl;
    for (int i = 1; i <= n; i++) {
        scanf("%d", arr + i);
    }
    while (getchar() != '\n') ;
    return ;
}

#endif // !INC_DEBUG_H_
