#include <iostream>
#include <limits.h>

using namespace std;
/**
 * Definition for a binary tree node.
 * */
struct TreeNode {
   int val;
   TreeNode *left;
   TreeNode *right;
   TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    int getMinimumDifference(TreeNode* root) {
        int minimum = INT_MAX;
        int val = -1;
        dfs(root,val,minimum);
        return minimum;
    }

private:
    void dfs(TreeNode* node, int& val, int& minimum) {
        if (node->left) dfs(node->left,val,minimum);

        if (val >= 0) minimum = min(minimum,node->val - val);
        val = node->val;

        if (node->right) dfs(node->right,val,minimum);
    }
};

int main(int argc, char const *argv[])
{
    TreeNode* node = new TreeNode(1);
    node->right = new TreeNode(3);
    node->right->left = new TreeNode(2);

    cout << Solution().getMinimumDifference(node) << endl;
    return 0;
}
