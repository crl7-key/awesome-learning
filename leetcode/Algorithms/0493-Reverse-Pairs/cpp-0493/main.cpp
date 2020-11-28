#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
        
    Solution() {
       ios::sync_with_stdio(false);
       cin.tie(0);
    }

    int reversePairs(vector<int>& nums) {
        return merge_sort(nums.data(), 0, nums.size());
   } 

private:
    void merge(int a[], int l, int m, int r) {
        int result[r - l];
        int ind = 0;
        int i1 = l, i2 = m;
        while (i1 < m || i2 < r) {
           if (i1 == m) {
               result[ind++] = a[i2];
                i2++;
            } else if (i2 == r) {
                result[ind++] = a[i1];
                i1++;
            } else if (a[i1] > a[i2]) {
                result[ind++] = a[i2];
                i2++;
            } else {
                result[ind++] = a[i1];
                i1++;
            }
        }
        for (int i = 0; i < r - l; i++) {
            a[l + i] = result[i];
        }
    }

    int merge_sort(int a[], int l, int r) {
        if (l >= r - 1)
            return 0;
        int mid = (l + r) / 2;
        int count = merge_sort(a, l, mid) + merge_sort(a, mid, r);
        int j = mid;
        for (int i = l; i < mid; i++) {
            while (j < r && a[i] > a[j] * 2LL)
                j++;
            count += j - mid;
        }
        
        merge(a, l, mid, r);
        return count;
    }
};

int main(int argc, char const *argv[])
{
    vector<int> nums {1,3,2,3,1};
    cout << Solution().reversePairs(nums) << endl;
    return 0;
}
