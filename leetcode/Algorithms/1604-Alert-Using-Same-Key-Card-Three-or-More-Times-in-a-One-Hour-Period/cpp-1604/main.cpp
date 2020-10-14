#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "output_container.h"

using namespace std;
class Solution {
public:
    vector<string> alertNames(vector<string>& keyName, vector<string>& keyTime) {
        unordered_map<string, vector<int>> record;
        auto toMinute = [](string& str) {
            return 60 * ((str[0] - '0') * 10 + str[1] - '0') + (str[3] - '0') * 10 + str[4] - '0';
        };
        for (int i = 0; i < keyName.size(); i++)
            record[keyName[i]].push_back(toMinute(keyTime[i]));
        
        vector<string> result;
        for (auto& r : record) {
            auto& time = r.second;
            sort(time.begin(), time.end());
            int pre = 0;
            for (int i = 0; i < time.size(); i++) {
                while (pre < i && time[i] - time[pre] > 60) {
                    pre++;
                }
                if (i - pre + 1 == 3) { // 超过三次
                    result.push_back(r.first);
                    break;
                }
            }
        }
        sort(result.begin(), result.end());
        return result;
    }
};

int main(int argc, char const *argv[])
{
    vector<string> keyName {"daniel","daniel","daniel","luis","luis","luis","luis"};
    
    vector<string> keyTime {"10:00","10:40","11:00","09:00","11:00","13:00","15:00"};

    cout << Solution().alertNames(keyName,keyTime) << endl;

    return 0;
}

