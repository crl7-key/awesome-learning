#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

/**
 * Definition for a binary tree node.
 * 
 * */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        unordered_map<int,int> m;
        for (int i = 0;i < inorder.size() ; ++i) {
            m[inorder[i]] = i;
        }
        return dfs(preorder,inorder,m,0,preorder.size() - 1, 0, inorder.size() - 1);
    }

private:
    TreeNode* dfs(vector<int>& preorder,vector<int>& inorder,unordered_map<int,int>& m,int preLeft,int preRight,int inLeft, int inRight) {
        if (preLeft > preRight) return NULL;
        TreeNode* node = new TreeNode(preorder[preLeft]);
        int pos = m[node->val];
        node->left = dfs(preorder,inorder,m,preLeft + 1, preLeft + pos - inLeft,inLeft,pos - 1);
        node->right = dfs(preorder,inorder,m,preLeft + pos - inLeft + 1,preRight,pos + 1,inRight);
        return node;
    }
};

int main(int argc, const char** argv) 
{
    return 0;
}
 