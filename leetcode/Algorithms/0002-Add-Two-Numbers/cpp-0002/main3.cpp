#include "list.h"
class Solution{
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode preHead(0), *ptr = &preHead;
        int carried = 0;

        while( l1 || l2 || carried ) {
            int sum = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + carried;
            carried = sum / 10;
            ptr->next = new ListNode(sum % 10);
            ptr = ptr->next;

            l1 = l1 ? l1->next : l1;
            l2 = l2 ? l2->next : l2;
        }
        return preHead.next;
    }
};

int main()
{
    auto list1 = generateListNode({2,4,3});
    auto list2 = generateListNode({5,6,4});

    printListNode(list1);
    printListNode(list2);

    Solution obj;
    auto ret = obj.addTwoNumbers(list1, list2);

    printListNode(ret);

    deleteListNode(list1);
    deleteListNode(list2);
    deleteListNode(ret);

    return 0;
}
