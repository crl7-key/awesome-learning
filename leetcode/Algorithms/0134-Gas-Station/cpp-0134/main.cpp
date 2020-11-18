#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = gas.size() -1;
        int right = 0;
        int sum = gas[n] - cost[n];
        
        while(n > right) {
            if(sum >= 0) {
                sum += gas[right] - cost[right];
                ++right;
            }
            else {
                --n;
                sum += gas[n] - cost[n];
            }
        } 
        return sum >= 0 ? n : -1;
    }
};

int main(int argc, const char** argv)
{
    vector<int> gas {1,2,3,4,5};
    vector<int> cost {3,4,5,1,2};
    
    std::cout << Solution().canCompleteCircuit(gas,cost) << std::endl;
    
    return 0;
}