#include <iostream>

using namespace std;

class Solution {
public:
    string replaceSpace(string s) {
        if (s.empty()) return s;
        string res = "";
        for(int i = 0; i < s.size() ; ++ i) {
            char c = s.at(i);
            if (c == ' ')res.append("%20");
            else res += c;
        }
        return res;
    }
};

int main(int argc, const char** argv)
{
    string s = "We are happy.";
    cout << Solution().replaceSpace(s) << endl;
    return 0;
}