#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

static const auto _ = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

//Time  Complexity: O(n)
//Space Complexity: O(n)

class Solution{
public:
    template<typename T>
        vector<T>twoSum(vector<T>& nums,int target){

            vector<int> v(2);
            unordered_map<int,int> record;
            for(int i = 0 ; i < nums.size();i ++) {
                record[nums[i]] = i;
            }

            for(int i = 0; i < nums.size(); i ++) {
                unordered_map<int,int>::iterator iter = record.find(target - nums[i]);

                if (iter != record.end() && iter->second != i) {
                    v[0] = iter->second ;
                    v[1] = i ;
                }
            }
            return v;
        }
};

template<typename T>
void print_ver(const vector<T>& vec) {
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
