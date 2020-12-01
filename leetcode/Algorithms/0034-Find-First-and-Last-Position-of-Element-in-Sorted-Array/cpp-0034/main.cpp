#include <iostream>
#include <vector>
#include "output_container.h"
using namespace std;


class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int startIndex = -1;
        int endIndex = -1;
        for(int i = 0 ;i < nums.size(); ++i) {
            if (nums[i] == target) {
                startIndex = i;
                break;
            }
        }
        
        if (startIndex == -1) return {-1, -1};

        for (int j = startIndex;j < nums.size(); ++j) {
            if (nums[j] != target){
                endIndex = j - 1;
                break;
            }
        }
        return {startIndex,endIndex};
    }
};

int main(int argc, char const *argv[])
{
    vector<int> nums {5,7,7,8,8,10};
    cout << Solution().searchRange(nums,8) << endl;
    return 0;
}
