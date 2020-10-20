#include <iostream>
#include <vector>

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

        vector<ListNode*> vec;
        ListNode* p = head;
        while(p) {
            vec.push_back(p);
            p = p->next;
        }
        int left = 0, right = vec.size() - 1;
        while(left < right) {
            vec[right - 1]->next = vec[right]->next;
            vec[right]->next = vec[left]->next;
            vec[left]->next = vec[right];
            ++left;
            --right;
        }
    }
};


int main(int argc, char const *argv[])
{
    
    return 0;
}


