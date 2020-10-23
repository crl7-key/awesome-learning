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
    bool isPalindrome(ListNode* head) {
        ListNode* p = head;
        stack<ListNode*> st;
        int cnt = 0; // 计算链表长度
        
        // 往栈放数据
        while(p){
            st.push(p);
            p = p->next;
            cnt++;
        }

        // 开始比较,此时栈顶的数据就是原始链表的尾数据
        for(int i = 0 ;i< cnt/2; i++){
            if(head->val != st.top()->val)
                return false;
            head = head->next;
            st.pop();
        }
    
        return true;
    }
    
};

int main(int argc, char const *argv[])
{
    
    return 0;
}
