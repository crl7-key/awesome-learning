#include <iostream>
#include <vector>
#include <algorithm>
#include "output_container.h"

using namespace std;

class Solution {
public:
    void sortColors(vector<int>& nums) {
       sort(nums.begin(),nums.end());
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