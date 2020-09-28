#include <iostream>
#include <vector>
/**
 * Definition for a Node.
 **/
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};


class Solution {
public:
    Node* connect(Node* root) {
        Node* pcur = root, *head = NULL, *tail = NULL;
        while(pcur) {
            if (pcur->left) {
                if (tail) {
                    tail = tail->next = pcur->left;
                }
                else {
                    head = tail = pcur->left;
                }
            }

            if (pcur->right) {
                if (tail) {
                    tail = tail->next = pcur->right;
                }
                else {
                    head = tail = pcur->right;
                }
            }
            if (!(pcur = pcur->next)) {
                pcur = head;
                head = tail = NULL;
            }
        }
        return root;
    }
};

int main(int argc, const char** argv) 
{
    
    return 0;
}