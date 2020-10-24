#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


class Solution {
public:
    int videoStitching(vector<vector<int>>& clips, int T) {
        int res = 0;
        sort(clips.begin(),clips.end());
        for(auto i = 0, start = 0, end = 0; start < T; start = end,res ++) {
            while(i < clips.size() && clips[i][0] <= start)  {
                end = max(end, clips[i++][1]);
            }
            if (start == end) return -1;
        }
        return res;
    }
};

int main(int argc, char const *argv[])
{
    vector<vector<int>> clips = {{0,2},{4,6},{8,10},{1,9},{1,5},{5,9}};
    cout << Solution().videoStitching(clips,10) << endl;
    return 0;
}
