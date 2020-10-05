#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
        if(matrix.size() == 0) return false;
        int height = matrix.size() - 1;
        int width = matrix[0].size() - 1;
        int pos = 0;
        //选取右上角的数据，(h = 0, width = matrix[0].size() - 1) 与target进行对比
        while(pos <= height && width >= 0) {
            if (matrix[pos][width] == target) return true;
            else if (matrix[pos][width] < target) pos++;
            else width--;
        }
        return false;
    }
};

int main(int argc, const char** argv) 
{
    
    return 0;
}
