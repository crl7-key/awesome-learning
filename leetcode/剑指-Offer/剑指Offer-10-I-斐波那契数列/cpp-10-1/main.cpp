#include <iostream>

using namespace std;

class Solution {
public:
    int fib(int n) {
        int a = 0, b = 1,sum; // 初始化前两个数字；
        for(int i = 0; i < n; ++i) {
            sum = (a + b)%(int)(1e9 + 7);
            a = b;
            b = sum;
        }
        return a;
    }
};

int main(int argc, char const *argv[])
{
    cout << Solution().fib(0) << endl;
    // output : 0
    return 0;
}
