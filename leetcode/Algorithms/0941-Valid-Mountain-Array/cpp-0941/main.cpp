#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool validMountainArray(vector<int>& A) {
        int n = A.size(); 
        int i = 0, j = n - 1;
        while(i + 1 < n && A[i] < A[i+1]) i++;

        while(j > 0 && A[j - 1] > A[j]) j--;

        return i > 0 && i == j && j < n -1;
    }
};

int main(int argc, char const *argv[])
{
    vector<int> A {2,1};
    cout << Solution().validMountainArray(A) << endl;
    return 0;
}
