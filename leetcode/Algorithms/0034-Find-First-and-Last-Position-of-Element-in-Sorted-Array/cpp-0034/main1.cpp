#include <iostream>
#include <vector>
#include "output_container.h"
using namespace std;


class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int index1 = lower_bound(nums,target);
        int index2 = lower_bound(nums,target +1) - 1;

        if (index1 < nums.size() && nums[index1] == target) {
            return {index1, index2};
        }
        else {
            return {-1,-1};
        }

    }

private:
    int lower_bound(vector<int>& nums,int target) {
        int left = 0, right = nums.size() - 1;
        while(left <= right) {
            int mid = (right - left) / 2 + left;
            if (nums[mid] < target) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        return left;
    }
};

int main(int argc, char const *argv[])
{
    vector<int> nums {5,7,7,8,8,10};
    cout << Solution().searchRange(nums,8) << endl;
    return 0;
}
