#include <iostream>
#include <string>

using namespace std;
static const auto _ = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    string addStrings(string num1, string num2) {
        int sum = 0;
        int p1 = num1.length() -1;
        int p2 = num2.length() -1;
        string str = "";
        while(p1 >= 0 || p2 >= 0 || sum > 0) {
            if (p1 >= 0) {
                sum += (num1[p1 --] - '0');
            }
            if (p2 >= 0) {
                sum += (num2[p2--] - '0');
            }
            str.insert(0,1,(sum %10) + '0');
            sum /= 10;
        }
        return str;
    }
};

int main()
{
    return 0;
}

