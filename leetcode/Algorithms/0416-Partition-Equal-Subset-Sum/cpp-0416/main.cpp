#include <iostream>
#include <vector>
#include <bitset>
#include <numeric>

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
        for (int i = 0; i < nums.size(); ++i) {
            sum += nums[i];
        }
        
        if (sum % 2) return false;
        sum /= 2;
        return helper(nums,sum,0);
    }
    
private:
    bool helper(vector<int>& nums,int sum , int index) {
        if (index == nums.size()) return false;
        if(sum == nums[index]) return true;
        if(sum < nums[index]) return false;
        return helper(nums,sum-nums[index],index+1) || helper(nums,sum,index+1);
    }
};

int main(int argc, char const *argv[])
{
    vector<int> nums {1,5,11,5};
    cout << Solution().canPartition(nums) << endl;
    return 0;
}