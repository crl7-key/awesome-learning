#include "thread_pool.h"
#include "HeapQueue.h"

void func(int a, int b) {
    std::cout << a << " + " << b << " = " << a + b << std::endl;
    return ;
}

int main(int argc, char const *argv[])
{
    ThreadPool<HeapQueue<Task *>> tp(5);
    std::this_thread::sleep_for(std::chrono::seconds(5));
    tp.addOneTask(new Task(func, 3, 4));
    tp.addOneTask(new Task(func, 5, 10));
    tp.addOneTask(new Task(func, 14, 60));
    std::this_thread::sleep_for(std::chrono::seconds(5));
    return 0;
}
