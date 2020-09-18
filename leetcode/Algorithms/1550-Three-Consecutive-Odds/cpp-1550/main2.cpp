#include "test.h"

class Solution {
public:
    bool threeConsecutiveOdds(vector<int>& arr) {
        if (arr.size() < 3) return false;
        for (int i = 0; i <= arr.size() - 3; ++ i){
            if ((arr[i] & 1) && (arr[i + 1] & 1) && (arr[i + 2] & 1)) return true;
        }

        return false;
    }
};

int main() {
    string line;
    while (getline(cin, line)) {
        vector<int> arr = stringToIntegerVector(line);

        bool ret = Solution().threeConsecutiveOdds(arr);

        string out = boolToString(ret);
        cout << out << endl;
    }
    return 0;
}
