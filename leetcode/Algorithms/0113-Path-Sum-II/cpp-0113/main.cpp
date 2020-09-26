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
 
class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int> > paths;
        vector<int> path;
        findPaths(root, sum, path, paths);
        return paths;  
    }
private:
    void findPaths(TreeNode* node, int sum, vector<int>& path, vector<vector<int> >& paths) {
        if (!node) return;
        
        path.push_back(node -> val);
        
        if (!(node -> left) && !(node -> right) && sum == node -> val)
            paths.push_back(path);
        findPaths(node -> left, sum - node -> val, path, paths);
        findPaths(node -> right, sum - node -> val, path, paths);
        path.pop_back();
    }
};

int main(int argc, const char** argv)
 {
     TreeNode *node = new TreeNode(5);
     node->left = new TreeNode(4);
     node->left->left = new TreeNode(11);
     node->left->left->left = new TreeNode(7);
     node->left->left->right = new TreeNode(2);
     node->right = new TreeNode(8);
     node->right->left = new TreeNode(13);
     node->right->right = new TreeNode(4);
     node->right->right->left = new TreeNode(5);
     node->right->right->right = new TreeNode(1);
    int sum = 22;
     cout << Solution().pathSum(node,sum) << endl;
    return 0;
}