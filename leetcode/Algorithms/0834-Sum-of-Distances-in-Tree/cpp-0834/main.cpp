#include <iostream>
#include <vector>
#include <unordered_set>
#include "output_container.h"

using namespace std;

class Solution {
public:
    Solution() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
    }

    vector<int> sumOfDistancesInTree(int N, vector<vector<int>>& edges) {
        vector<unordered_set<int>> tree;
        vector<int> res;
        vector<int> count;
        tree.resize(N);
        res.assign(N, 0);
        count.assign(N, 1);
        for (auto e : edges) {
            tree[e[0]].insert(e[1]);
            tree[e[1]].insert(e[0]);
        }
        dfs(tree,res,count,0,-1);
        dfs2(tree,res,count,0,-1);
        return res;
    }

private:
    void dfs(vector<unordered_set<int>>& tree,vector<int>& res,vector<int>& count,int root,int pre) {
        for (auto i : tree[root]) {
            if (i == pre) continue;
            dfs(tree,res,count,i, root);
            count[root] += count[i];
            res[root] += res[i] + count[i];
        }
    }

    void dfs2(vector<unordered_set<int>>& tree,vector<int>& res,vector<int>& count,int root,int pre) {
        for (auto i : tree[root]) {
            if (i == pre) continue;
            res[i] = res[root] - count[i] + count.size() - count[i];
            dfs2(tree,res,count,i,root);
        }
    }
};

int main(int argc, const char** argv) 
{
    vector<vector<int>> edges{{0,1},{0,2},{2,3},{2,4},{2,5}};

    cout << Solution().sumOfDistancesInTree(6,edges) << endl;
    
    return 0;
}