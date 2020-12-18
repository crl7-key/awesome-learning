#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    char findTheDifference(string s, string t) {
        vector<int> cnt(26, 0);
        for (char ch: s) {
            cnt[ch - 'a']++;
        }
        for (char ch: t) {
            cnt[ch - 'a']--;
            if (cnt[ch - 'a'] < 0) {
                return ch;
            }
        }
        return ' ';
    }
};

int main(int argc, char const *argv[])
{
    string s = "abc";
    string t = "abcde";
    cout << Solution().findTheDifference(s,t) << endl;
    return 0;
}
