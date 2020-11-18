#include <iostream>
#include <vector>
#include "output_container.h"

using namespace std;

class Solution {
public:
    vector<vector<int>> allCellsDistOrder(int R, int C, int r0, int c0) {
        auto comp = [r0,c0](const vector<int> &a , const vector<int> &b) {
            return abs(a[0]- r0) + abs(a[1]- c0) < abs(b[0] - r0) + abs(b[1] - c0);
        };
        
        vector<vector<int>> res;
        for(int i = 0 ; i < R; ++i) {
            for(int j = 0; j < C; ++j) {
                res.push_back({i,j});
            }
        }
        sort(res.begin(),res.end(),comp);
        
        return res;
    }
};

int main(int argc, char const *argv[])
{
    int R = 2,C = 3, r0 = 1, c0 = 2;
    
    std::cout << Solution().allCellsDistOrder(R,C,r0,c0) << std::endl;

    return 0;
}
