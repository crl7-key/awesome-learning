#ifndef INC_HEAP_QUEUE_H_
#define INC_HEAP_QUEUE_H_

#include <vector>
#include <functional>

// 优先队列
template<
    typename T, 
    typename Array=std::vector<T>, 
    typename compare_T=std::less<T>
>
class HeapQueue {
public :
    HeapQueue() { elements.clear(); }
    bool empty() { return elements.size() == 0; }
    T front() { return elements[0]; }
    // 入队,并向上调整
    void push(const T &val) {
        elements.push_back(val);
        up_update();
        return ;
    }
    // 出队,弹出堆顶元素
    void pop() {
        if (empty()) return ;
        int index = 0, n = elements.size();
        std::swap(elements[n - 1], elements[0]);
        elements.pop_back();
        down_update();
        return ;
    }

private:
    Array elements;
    compare_T compare;
    // 向上调整
    void up_update() {
        int index = elements.size();
        while (index > 1 && 
               compare(elements[index / 2 - 1], elements[index - 1])) {
            std::swap(elements[index / 2 - 1], elements[index - 1]);
            index /= 2;
        }
        return ;
    }
    // 向下调整
    void down_update() {
        int index = 0, n = elements.size();
        while (index * 2 + 1 < n) {
            int tmp = index;
            if (compare(elements[tmp], elements[index * 2 + 1])) {
                tmp = index * 2 + 1;
            }
            if (index * 2 + 2 < n &&
                compare(elements[tmp], elements[index * 2 + 2])) {
                tmp = index * 2 + 2;
            }
            if (index == tmp) break;
            std::swap(elements[index], elements[tmp]);
            index = tmp;
        }
        return ;
    }
};
#endif // !INC_HEAP_QUEUE_H_