#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "output_container.h"

using namespace std;

class Solution {
public:
    vector<string> commonChars(vector<string>& A) {
        vector<unordered_map<char,int>> record(A.size()); // 记录每个元素表示每个字符串中字母的统计情况
        vector<string> res;
        
        for(int i = 0; i < A.size(); ++i) {
            for(auto ch : A[i]) {
                record[i][ch]++;
            }
        }
        
        for(auto p : record[0]) {
            int n = p.second;
            for (int i = 0; i < record.size(); ++i) {
                n = min(n,record[i][p.first]);
            }
            
            while(n--) {
                res.push_back(string(1,p.first));
            }
        }
        
        return res;
    }
};

int main(int argc, char const *argv[])
{
    vector<string> vec {"bella","label","roller"};

    cout << vec << endl;

    cout << Solution().commonChars(vec) << endl;
    return 0;
}
