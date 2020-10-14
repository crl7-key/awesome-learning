#include <vector>
#include <iostream>
#include "output_container.h"
using namespace std;


class Solution {
public:
    vector<vector<int>> restoreMatrix(vector<int>& rowSum, vector<int>& colSum) {
        int row = rowSum.size(), col = colSum.size();
        vector<vector<int>> vec(row,vector<int>(col,0));
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                vec[i][j] = min(rowSum[i],colSum[j]);
                rowSum[i] -= vec[i][j];
                colSum[j] -= vec[i][j];
            }
        }
        return vec;
    }
};

int main(int argc, char const *argv[])
{
    vector<int> rowSum {3,8};
    vector<int> colSum {4,7};

    cout << Solution().restoreMatrix(rowSum,colSum) << endl;
    
    return 0;
}

