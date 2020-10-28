#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
public:
    bool uniqueOccurrences(vector<int>& arr) {
        unordered_map<int,int> record;
        for(auto i : arr) {
            record[i]++;
        }
        
        unordered_set<int> cache;
        for(auto i : record) {
            cache.insert(i.second);
        }
        return cache.size() == record.size();
    }
};

int main(int argc, char const *argv[])
{
    vector<int> arr {1,2,2,1,1,3};
    cout << Solution().uniqueOccurrences(arr) << endl;
    return 0;
}
