#include <iostream>

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
    bool isPalindrome(ListNode* head) {
        ListNode* fast = head;
        ListNode* slow = head;
        while(fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        ListNode* prev = NULL;
        while(head != slow) {
            ListNode* next = head->next;
            head->next = prev;
            prev = head;
            head = next;
        }
        
        if (fast) {
            slow = slow->next;
        }
        
        while(slow && prev) {
            if(slow->val != prev->val) 
                return false;
            slow = slow->next;
            prev = prev->next;
            
        }
        return true;
    }
    
};

int main(int argc, char const *argv[])
{
    
    return 0;
}
