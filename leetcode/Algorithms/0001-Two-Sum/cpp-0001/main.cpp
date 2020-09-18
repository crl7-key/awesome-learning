#include <iostream>
#include <vector>

using namespace std;

//Time  Complexity: O(n^2)
//Space Complexity: O(1)
class Solution{
public:
    template<typename T>
        vector<T>twoSum(vector<T>& nums,int target){

            vector<int> v(2);
            for(int i = 0 ; i < nums.size();i ++) {
                for (int j = i + 1; j < nums.size();j ++) {
                    if(nums[i] + nums[j] == target) {
                        v[0] = i;
                        v[1] = j;
                    }        
                } 
            } 
            return v;
        }

};
template<typename T>
void print_ver(const vector<T>& vec){
    for (auto e: vec)
        cout << e << " ";
    cout << endl;
}

int main()
{
    vector<int> nums = {2, 7, 11, 15};
    int target;
    cout << "please input target: ";
    cin>>target;
    print_ver(Solution().twoSum(nums,target));
    return 0;
}

