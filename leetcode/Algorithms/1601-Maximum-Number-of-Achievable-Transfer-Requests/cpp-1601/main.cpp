#include <iostream>
#include <vector>

using namespace std;


class Solution {
public:
    int maximumRequests(int n, vector<vector<int>>& requests) {
        vector<int> vec(n,0);
        int res = 0;
        helper(requests,vec,0,0,res);
        return res;
    }

private:
    void helper(vector<vector<int>>& requests,vector<int> &vec,int reqId,int reqProcessed,int &res) {
        if (reqId == requests.size()) {
            for (auto p : vec) {
                if (p != 0) {
                    return;
                }
            }
            res = max(res,reqProcessed);
                return;
        }

        helper(requests,vec,reqId + 1,reqProcessed,res);

        vec[requests[reqId][0]] --;
        vec[requests[reqId][1]] ++;

        helper(requests,vec,reqId + 1,reqProcessed + 1,res);
        vec[requests[reqId][0]] ++;
        vec[requests[reqId][1]] --;
    }
};

int main(int argc, const char** argv)
{
    return 0;
}