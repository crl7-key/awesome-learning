#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

//Time  Complexity: O(n)
//Space Complexity: O(n)

static const auto _ = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution{
public:
    template<typename T>
        vector<T>twoSum(vector<T>& nums,int target){

            //key是数字,键值为vector中的索引
            unordered_map<int,int> record;
            vector<int> result;

            for(int i = 0; i < nums.size(); ++i) {
                int found = target - nums[i];
                //如果在map中找到了target，返回 
                if (record.find(found) != record.end()){
                    result.push_back(record[found]);
                    result.push_back(i);
                    return result;
                }
                //如果没有找到，将其放在map中
                record[nums[i]] = i;
            }
            return result;
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
