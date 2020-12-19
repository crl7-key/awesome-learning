#include <iostream>
#include <vector>
#include "output_container.h"

using namespace std;

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        for(int i = 0; i < matrix.size() / 2; i++ ) {
            swap(matrix[i],matrix[matrix.size() - 1 - i]);
        }
        for (int i = 0; i < matrix.size(); i ++) {
            for (int j = i; j < matrix.size(); j ++) {
                swap(matrix[i][j],matrix[j][i]);
            }
        }
    }
};

int main(int argc, char const *argv[])
{
    vector<vector<int>> matrix = {{1,2,3},{4,5,6},{7,8,9}};
    cout << matrix << endl;
    Solution().rotate(matrix);
    cout << matrix << endl;
    return 0;
}
