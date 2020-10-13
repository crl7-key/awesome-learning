#include <iostream>

/**
 * Definition for singly-linked list.
 * */
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if (!head || !head->next)return head;
        ListNode* node = head->next;
        head->next = swapPairs(node->next);
        node->next = head;
        
        return node;
    }
};

int main(int argc, char const *argv[])
{
    
    return 0;
}
