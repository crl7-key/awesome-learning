#include <iostream>
#include <vector>
#include "output_container.h"

using namespace std;

class Solution {
public:
    void reverseString(vector<char>& s) {
        int left = 0, right = s.size() - 1;
        
        while(left < right) {
            s[left] ^= s[right];
            s[right] ^= s[left];
            s[left] ^= s[right];
            left ++;
            right --;
        }
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