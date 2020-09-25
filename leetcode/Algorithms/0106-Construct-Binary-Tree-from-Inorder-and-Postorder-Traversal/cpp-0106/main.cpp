/**
 * Definition for a binary tree node.
 * */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include "output_container.h"

using namespace std;

 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
static const auto _ = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        return helper(inorder,0,inorder.size(),postorder,0,postorder.size());
    }
private:
    TreeNode* helper(vector<int>& inorder,int i,int j,vector<int>& postorder,int ii,int jj) {
        if(i >= j || ii >= jj) return NULL;
        // 每次取postorder的最后一个值mid，将其作为树的根节点
        int mid = postorder[jj - 1];
        // 从inroder中找到mid，将其分割成为两部分，左边作为mid的左子树，右边作为mid的右子树
        auto f = find(inorder.begin() + i,inorder.begin() + j,mid);
        
        int tmp = f - inorder.begin() - i;
        
        TreeNode* node = new TreeNode(mid);
        node->left = helper(inorder,i,i + tmp,postorder,ii,ii + tmp);
        node->right = helper(inorder,i + tmp + 1,j,postorder,ii + tmp,jj - 1);
        
        return node;
    }
};

vector<int> TreeToVector(TreeNode* node) {
    queue<TreeNode*> q;
    vector<int> res;
    if(node == nullptr){
        return res;
    }
    q.push(node);
    while(!q.empty()) {
        int len = q.size();
        for(int i = 0; i < len; i++) {
            TreeNode* temp = q.front();
            q.pop();
            if(temp != nullptr) {
                res.push_back(temp->val);
            }
            if(temp->left) {
                q.push(temp->left);
            }
            if(temp->right) {
                q.push(temp->right);
            }
        }
    }
    return res;
}


int main(int argc, const char** argv) 
{
    vector<int> inorder{9,3,15,20,7};
    vector<int> postorder{9,15,7,20,3};
    cout << inorder << endl;
    cout << postorder << endl;
    TreeNode* node = Solution().buildTree(inorder, postorder);
    vector<int> res = TreeToVector(node);
    cout << res << endl;
    return 0;
}

 