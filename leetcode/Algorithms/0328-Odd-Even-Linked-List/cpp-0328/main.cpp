#include <iostream>


/**
 * Definition for singly-linked list.
 **/
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        if (!head || !head->next || !head->next->next) return head;

        ListNode* odd = head;   // 遍历奇数节点
        ListNode* evenhead = head->next; // 保存偶数节点起始位置
        ListNode* even = evenhead;       // 遍历偶数节点

        while(even && even->next) { 
            odd->next = odd->next->next;
            even->next = even->next->next;

            odd = odd->next;
            even = even->next;
        }
        odd->next = evenhead;
        return head;
    }
};

int main(int argc, char const *argv[])
{
    
    return 0;
}
