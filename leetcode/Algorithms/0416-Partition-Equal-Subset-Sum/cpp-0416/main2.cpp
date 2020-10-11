#include <iostream>
#include <vector>
#include <bitset>
#include <numeric>

using namespace std;

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum & 1) return false;
        bitset<10'001> dp = 1;
        for (auto num : nums) dp |= dp << num;
        return dp[sum >> 1];
    }
};

int main(int argc, char const *argv[])
{
    vector<int> nums {1,5,11,5};
    cout << Solution().canPartition(nums) << endl;
    return 0;
}

     