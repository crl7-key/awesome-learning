#include <iostream>
#include <vector>
#include "output_container.h"

using namespace std;

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> tmp;
        subsets(nums,res,tmp,0);
        return res;
    }

private:
    void subsets(vector<int>& nums,vector<vector<int>> & res,vector<int> &tmp,int index) {
        res.push_back(tmp);
        for(int i = index; i < nums.size(); ++i) {
            tmp.push_back(nums[i]);
            subsets(nums,res,tmp,i + 1);
            tmp.pop_back();
        }
    }
};
int main()
{
    vector<int> nums {1,2,3};
    cout << Solution().subsets(nums) << endl;
    return 0;
}

