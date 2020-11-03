#include <iostream>
#include <vector>
#include "output_container.h"

using namespace std;

class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> res;
        
        for (int i = 0; i < intervals.size(); i++) {
            // 新的间隔在其他间隔的范围之后，因此可以保留当前间隔,因为新的间隔不与之重叠
            if (intervals[i][1] < newInterval[0]) {
                res.push_back(intervals[i]);
            }
			// 新间隔的范围在另一个间隔之前,因此可以添加新间隔并将其更新为当前间隔
            else if (intervals[i][0] > newInterval[1]) {
                res.push_back(newInterval);
                newInterval = intervals[i]; 
            }
            // 新的间隔在另一个间隔的范围内会有一个重叠，因此需要为间隔的开始选择最小值,为结束选择最大值
            else if(intervals[i][1] >= newInterval[0] || intervals[i][0] <= newInterval[1]) {
                newInterval[0] = min(intervals[i][0], newInterval[0]);
                newInterval[1] = max(newInterval[1], intervals[i][1]);

            }
        }
        
        res.push_back(newInterval); 
        return res;
    }
};

int main(int argc, char const *argv[])
{
    vector<vector<int>> intervals {{1,3},{2,5}};
    vector<int> newInterval {2,5};

    cout << Solution().insert(intervals,newInterval) << endl;

    return 0;
}
