/**
 * Definition for a binary tree node.
 *
 * */ 

#include <iostream>

using namespace std;

static const auto _ =[]() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

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
    int minCameraCover(TreeNode* root) {
        int minSum = 0;
        if (minCameraCover(root,minSum) == 0) minSum++;
        return minSum;
    }

private:
    int minCameraCover(TreeNode* node,int &sum) {
        if (!node) return 1;
        int left = minCameraCover(node->left,sum);
        int right = minCameraCover(node->right,sum);
        if (left == 0 || right == 0) {
            sum++;
            return 2;
        }
        else if (left == 2 || right == 2) {
            return 1;
        }
        else {
            return 0;
        }
        return -1;
    }
};

int main()
{
    TreeNode* node = new TreeNode(0);
    node->left = new TreeNode(0);
    node->left->left = new TreeNode(0);
    node->left->right = new TreeNode(0);
    cout << Solution().minCameraCover(node) << endl;
    return 0;
}