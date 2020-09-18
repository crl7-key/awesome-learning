#include "list.h"
class Solution{
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {

        ListNode* p1 = l1, *p2 = l2;
        ListNode* dummyhead = new ListNode(-1);
        ListNode* pcur = dummyhead;
        int carried = 0;

        while( p1 || p2 ){
            int a = p1 ? p1->val : 0;
            int b = p2 ? p2->val : 0;
            pcur->next = new ListNode((a + b + carried) % 10);
            carried = (a + b + carried)/10;

            pcur = pcur->next;

            p1 = p1 ? p1->next : NULL;
            p2 = p2 ? p2->next : NULL;
        }
        pcur->next = carried ? new ListNode(1):NULL;    
        ListNode* pret = dummyhead->next;
        delete dummyhead;
        return pret;
    }
};

int main()
{
    auto list1 = generateListNode({2,4,3});
    auto list2 = generateListNode({5,6,4});

    printListNode(list1);
    printListNode(list2);

    Solution obj;
    auto list3 = obj.addTwoNumbers(list1, list2);

    printListNode(list3);

    deleteListNode(list1);
    deleteListNode(list2);
    deleteListNode(list3);
    return 0;
}

