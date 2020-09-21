/**
 * Definition for a binary tree node.
 **/ 


#include <iostream>
#include <vector>

using namespace std;

static const auto _ = [] () {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
 
class Solution {
public:
    TreeNode* convertBST(TreeNode* root) {
        int sum = 0;
        return convertBST(root,sum);
    }

private:
    TreeNode* convertBST(TreeNode* node , int &sum) {
        if (!node) return NULL;
        convertBST(node->right,sum);
        sum += node->val;
        node->val = sum;
        convertBST(node->left,sum);
        return node; 
    }
};


int main()
{
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(2);
    root->right = new TreeNode(13);

    TreeNode* p = Solution().convertBST(root);
    cout << "[ " << p->val << " , " << p->left->val << " , " << p->right->val << " ]" << endl;
    return 0;

}