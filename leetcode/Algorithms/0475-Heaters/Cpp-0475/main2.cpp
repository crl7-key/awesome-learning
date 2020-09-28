#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>

using namespace std;

class Solution {
public:
    Solution() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
    }
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        int res = 0;
        sort(heaters.begin(),heaters.end());
        for (const auto & p : houses) {
            // 二分查找不小于houses的第一个值
            auto pcur = lower_bound(begin(heaters),end(heaters),p);
            int i = (pcur == begin(heaters) ? INT_MAX : p - *prev(pcur));
            int j = (pcur == end(heaters) ? INT_MAX : *pcur - p);
            res = max(res,min(i,j));
        }
        return res;
    }
};

int main(int argc, const char** argv) 
{
    vector<int> houses{1,2,3};
    vector<int> heaters{2};
    cout << Solution().findRadius(houses,heaters) << endl;
    return 0;
}