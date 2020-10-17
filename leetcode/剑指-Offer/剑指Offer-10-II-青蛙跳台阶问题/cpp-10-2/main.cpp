#include <iostream>

using namespace std;

class Solution {
public:
    int numWays(int n) {
        int a = 1, b = 1,sum; // 初始化前两个数字；
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
    cout << Solution().numWays(0) << endl;
    // output : 1
    return 0;
}
