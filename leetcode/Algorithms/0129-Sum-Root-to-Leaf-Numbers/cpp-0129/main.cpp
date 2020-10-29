#include <iostream>

using namespace std;
/**
 * Definition for a binary tree node.
 **/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
 
class Solution {
public:
    int sumNumbers(TreeNode* root) {
        return sumNumbers(root,0);
    }
    
private:
    int sumNumbers(TreeNode* node,int n) {
        if (!node) return 0;
        
        if (!node->left && !node->right) return n * 10 + node->val;
        
        return sumNumbers(node->left,n * 10 + node->val) + sumNumbers(node->right,n * 10 + node->val);
    }
};

int main(int argc, char const *argv[])
{
    return 0;
}
