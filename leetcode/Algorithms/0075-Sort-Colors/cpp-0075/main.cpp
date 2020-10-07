#include <iostream>
#include <vector>
#include "output_container.h"

using namespace std;

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int tmp = 0, low = 0 , mid = 0, high = nums.size() - 1;
        
        while(mid <= high) {
             if(nums[mid] == 0) {
                tmp = nums[low];
                nums[low] = nums[mid];
                nums[mid] = tmp;
                low++;
                mid++;
            }
            else if(nums[mid] == 1) {
                mid++;
            }
            else if(nums[mid] == 2) {
                tmp = nums[high];
                nums[high] = nums[mid];
                nums[mid] = tmp;
                high--;
            }
        }
    }
};

int main(int argc, const char** argv)
{
    vector<int> nums {2,0,2,1,1,0};

    cout << nums << endl;

    Solution().sortColors(nums);
    
    cout << nums << endl;
    return 0;
}