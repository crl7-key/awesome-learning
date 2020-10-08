#include <iostream>
#include <vector>
#include <algorithm>
#include "output_container.h"

using namespace std;

class Solution {
public:
    void reverseString(vector<char>& s) {
        reverse(s.begin(),s.end());
    }
};

int main(int argc, const char** argv) 
{
    vector<char> s {'h','e','l','l','o'};
    cout << s << endl;

    Solution().reverseString(s);

    cout << s << endl;
    return 0;
}