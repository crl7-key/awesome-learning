#include <iostream>
#include <stack>

using namespace std;
class CQueue {
public:
    CQueue() {

    }
    void appendTail(int value) {
        stack_in.emplace(value);
    }
    
    int deleteHead() {
        if (stack_out.empty()) {
            while(!stack_in.empty()) {
                stack_out.push(stack_in.top());
                stack_in.pop();
            }
        }
        if (stack_out.empty()) return -1;
        int res = stack_out.top();
        stack_out.pop();
        return res;
    }
private:
stack<int> stack_in, stack_out;
};

/**
 * Your CQueue object will be instantiated and called as such:
 * CQueue* obj = new CQueue();
 * obj->appendTail(value);
 * int param_2 = obj->deleteHead();
 */

int main(int argc, char const *argv[])
{
    return 0;
}
