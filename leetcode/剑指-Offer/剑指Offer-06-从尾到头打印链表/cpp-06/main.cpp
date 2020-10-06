#include <iostream>
#include <stack>
#include <vector>
#include "output_container.h"

using namespace std;

/**
 * Definition for singly-linked list.
 **/
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
 };
 
class Solution {
public:
    vector<int> reversePrint(ListNode* head) {
        stack<int> st;
        vector<int> res;
        while(head) {
            st.push(head->val);
            head = head->next;
        }
        while(!st.empty()) {
            res.push_back(st.top());
            st.pop();
        }
        return res;
    }
};

int main(int argc, const char** argv) 
{
    ListNode* node = new ListNode(1);
    node->next = new ListNode(3);
    node->next->next = new ListNode(2);
    cout << Solution().reversePrint(node) << endl;
    return 0;
}