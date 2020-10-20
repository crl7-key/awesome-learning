#include <iostream>
#include <stack>

using namespace std;


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
    void reorderList(ListNode* head) {
        if(!head || !head->next || !head->next->next) return;

        stack<ListNode*> tmp_st;
        ListNode* p = head;
        int len = 0;
        while(p) { // 将链表压入栈中
            tmp_st.push(p);
            len++;
            p = p->next;
        }

        ListNode* record = head;
        for(int i = 0; i < len/2 ; ++i) { // 在每两个节点之间，将一个插入到堆栈的顶部
            ListNode* tmp = tmp_st.top();
            tmp_st.pop();
            tmp->next = record->next;
            record->next = tmp;
            record = record->next->next;
        }
        record->next = NULL;
    }
};


int main(int argc, char const *argv[])
{
    
    return 0;
}


