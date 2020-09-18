#ifndef INC_LIST_H_
#define INC_LIST_H_
#include <vector>
#include <iostream>

using namespace std;

typedef struct ListNode_{
    int val;
    ListNode_ *next;
    ListNode_(int x):val(x),next(NULL){}
}ListNode;

ListNode* generateListNode(vector<int> vals) {

    ListNode *res = NULL;
    ListNode *last = NULL;
    for(auto v : vals) {
        if (last) {
            last->next = new ListNode(v);
            last = last->next;
        }else{
            res = new ListNode(v);
            last = res;
        }
    }
    return res;
}

void deleteListNode(ListNode* head) {
    ListNode* ptr = head;
    while(ptr) {
        auto tmp = ptr->next;
        delete ptr;
        ptr = tmp;
    }
}

void printListNode(ListNode* head) {
    ListNode* ptr = head;
    cout << '[';
    while(ptr) {
        cout << ptr->val;
        if (ptr->next != NULL) {
            cout << " , ";
        }
        ptr = ptr->next;
    }
    cout << "]" <<endl;
}

#endif //INC_LIST_H
