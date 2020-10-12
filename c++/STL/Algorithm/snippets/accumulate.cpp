#include <iostream>
#include <numeric>
#include <vector>
#include <string>

int myFunction(const int &x, const int &y) {
    return x * y;
}

int main()
{
    std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int sum = std::accumulate(v.begin(), v.end(), 0);   // 计算 0 和 v[first,last) 内所有元素的总和
    std::cout << "sum: " << sum << std::endl;           // ouput :   sum : 55
    
    // 自定义的回调函数
    auto dash_fold = [](std::string a, int b) {
                         return std::move(a) + '-' + std::to_string(b);
                     };
                     
    std::string str = std::accumulate(std::next(v.begin()), v.end(),
                                    std::to_string(v[0]), // start with first element
                                    dash_fold);   
    
    std::cout << "dash-separated string: " << str << std::endl; // output :  dash-separated string: 1-2-3-4-5-6-7-8-9-10 
 
    std::cout<< accumulate(v.begin(),v.end(),1,myFunction)<<std::endl;
    
    return 0;
}
