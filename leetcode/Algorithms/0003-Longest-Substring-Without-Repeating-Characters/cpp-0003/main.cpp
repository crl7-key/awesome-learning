#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int recordLen = 0, start = -1;
        vector<int> v(256,-1);
        for(int i = 0; i < s.size(); ++i) {
            if(v[s[i]] > start) {
                start = v[s[i]];
            }
            v[s[i]] = i;
            recordLen = max(recordLen,i - start);
        }
        return recordLen;
    }
};

int main(int argc, char const *argv[])
{
    cout << Solution().lengthOfLongestSubstring("abcabcbb") << endl;
    return 0;
}
