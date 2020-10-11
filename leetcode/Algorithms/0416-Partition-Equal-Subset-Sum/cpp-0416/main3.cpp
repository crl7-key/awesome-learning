#include <iostream>
#include <vector>

using namespace std;

static const auto _ = []{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        for (auto num : nums) sum += num;

        if (sum % 2) return false;
        sum /= 2;
        vector<int> dp(sum + 1,0);
        dp[0] = 1;

        for (int i = 0; i < nums.size(); ++i) {
            for (int j = sum; j >= nums[i]; --j) {
                dp[j] |= dp[j - nums[i]];
                if (j == sum && dp[j]) return true;
            }
        }
        return false;
    }
};

int main(int argc, char const *argv[])
{
    vector<int> nums {1,5,11,5};
    cout << Solution().canPartition(nums) << endl;
    return 0;
}

     