#include <iostream>
#include <vector>
#include "output_container.h"
using namespace std;
/**
 * Definition for a binary tree node.
 * */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };
 
 // 后序遍历: 左 - 右 - 根
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        // 递归
        helper(root,res);
        return res;
    }
private:
    void helper(TreeNode* node, vector<int>& res) {
        if (!node) return;

        helper(node->left,res);   // 左
        helper(node->right,res);  // 右
        res.push_back(node->val); // 中
    }
};

int main(int argc, const char** argv) 
{
    TreeNode* node = new TreeNode(1);
    node->right = new TreeNode(2);
    node->right->left = new TreeNode(3);
    
    cout << Solution().postorderTraversal(node) << endl;
    return 0;
}