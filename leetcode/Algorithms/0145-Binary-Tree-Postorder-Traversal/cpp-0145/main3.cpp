#include <iostream>
#include <vector>
#include "output_container.h"
#include <algorithm>

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
        if(!root) return res;

        TreeNode* dummyRoot = new TreeNode(-1);
        dummyRoot->left = root;

        TreeNode* cur = dummyRoot;
        while(cur != NULL){
            if(cur->left == NULL)
                cur = cur->right;
            else {
                TreeNode* prev = cur->left;
                while(prev->right != NULL && prev->right != cur)
                    prev = prev->right;

                if(prev->right == NULL){
                    prev->right = cur;
                    cur = cur->left;
                }
                else{
                    prev->right = NULL;
                    reverseTraversal(cur->left, res);
                    cur = cur->right;
                }
            }
        }
        delete dummyRoot;

        return res;
    }

private:
    void reverseTraversal(TreeNode* node, vector<int>& res){

        int start = res.size();
        while(node != NULL){
            res.push_back(node->val);
            node = node->right;
        }
        reverse(res.begin() + start, res.end());
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