#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int longestMountain(vector<int>& A) {
        int n = A.size();
        int res = 0, index = 0;
        while(index < n) {
            int tmp = index;
            if (tmp + 1 < n && A[tmp] < A[tmp + 1]) {
                while( tmp + 1 < n && A[tmp] < A[tmp + 1]) tmp++;

                if (tmp + 1 < n && A[tmp] > A[tmp + 1]) {
                    while(tmp + 1 < n && A[tmp] > A[tmp + 1]) tmp++;
                    res = max(res,tmp - index + 1);
                }
            }
            index = max(tmp,index + 1);
        }
        return res;
    }
};

int main(int argc, char const *argv[])
{
    vector<int> A {2,1,4,7,3,2,5};
    cout << Solution().longestMountain(A) << endl;
    return 0;
}
