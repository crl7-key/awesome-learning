#include "test.h"

class Solution {
public:
    bool threeConsecutiveOdds(vector<int>& arr) {
        int count = 0;
        for (int i : arr) {
            if (i % 2 == 1) {
                count++;
                if (count == 3) {
                    return true;
                }
            }
            else {
                count = 0;
            }
        }
        return false;
    }
};

int main() {

    int n = 10000;
    int* a = generateRandomArray<int>(n,0,n);
    vector<int> arr(a,a+n);
    bool ret = Solution().threeConsecutiveOdds(arr);

    string out = boolToString(ret);
    cout << out << endl;
    return 0;
}
