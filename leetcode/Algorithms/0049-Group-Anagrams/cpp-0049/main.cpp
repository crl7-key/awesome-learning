#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include "output_container.h"

using namespace std;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> mp;
        for (string& str: strs) {
            string key = str;
            sort(key.begin(), key.end());
            mp[key].emplace_back(str);
        }
        vector<vector<string>> ans;
        for (auto it = mp.begin(); it != mp.end(); ++it) {
            ans.emplace_back(it->second);
        }
        return ans;
    }
};

int main(int argc, char const *argv[])
{
    vector<string> strs {"eat","tea","tan","ate","nat","bat"};
    cout << Solution().groupAnagrams(strs) << endl;

    return 0;
}
