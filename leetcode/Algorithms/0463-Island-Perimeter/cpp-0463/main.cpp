#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        int res = 0;
        for(int i = 0; i < grid.size(); ++i) {
            for(int j = 0; j < grid[0].size(); ++j) {
                if (grid[i][j] == 0) continue; // 判断是否为陆地，如果为水域继续
                
                if (i == 0 || grid[i -1 ][j] == 0) res++; // 判断上边是否有相邻

                if (j == 0 || grid[i][j-1] == 0) res++; // 判断左边是否有相邻

                if (i == grid.size() - 1  || grid[i+1][j] == 0) res++; // 判断下边是否有相邻

                if (j == grid[0].size() - 1 || grid[i][j+1] == 0) res++; // 判断右边是否有相邻
            }
        }
        return res;
    }
};

int main(int argc, char const *argv[])
{
    vector<vector<int>> grid = {{0,1,0,0},{1,1,1,0},{0,1,0,0},{1,1,0,0}};

    cout << Solution().islandPerimeter(grid) << endl;
    
    return 0;
}


