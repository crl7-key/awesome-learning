#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// 前序遍历 : 根节点 — 左子树 — 右子树

class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> result;
        // 递归 
        __preorderTraversal(root,result);
        return result;
    }

private:
    void __preorderTraversal(TreeNode* node , vector<int>& v) {
        if (node) {
            v.push_back(node->val);             // 根节点
             __preorderTraversal(node->left,v); // 左子树
             __preorderTraversal(node->right,v);// 右子树
        }
    }        
};