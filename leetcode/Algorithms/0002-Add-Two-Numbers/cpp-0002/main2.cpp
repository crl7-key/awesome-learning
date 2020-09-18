#include "list.h"
class Solution{
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {

        ListNode* p1 = l1, *p2 = l2;
        ListNode* pcur = NULL;
        int carried = 0;

        while( p1 || p2 ){
            int a = p1 ? p1->val : 0;
            int b = p2 ? p2->val : 0;
            if(p1) {
                p1->val = ( a + b + carried) % 10;
            }
            else{
                pcur->next = new ListNode((a + b + carried) % 10);
                p1 = pcur->next;
            }
            carried = (a + b + carried)/10;

            pcur = p1;
            p1 = p1->next;

            if(p2) p2 = p2->next;
        }
        pcur->next = carried ? new ListNode(1) : NULL;
        return l1;
    }
};

int main()
{
    auto list1 = generateListNode({2,4,3});
    auto list2 = generateListNode({5,6,4});

    printListNode(list1);
    printListNode(list2);

    Solution obj;
    obj.addTwoNumbers(list1, list2);

    printListNode(list1);

    deleteListNode(list1);
    deleteListNode(list2);

    return 0;
}

