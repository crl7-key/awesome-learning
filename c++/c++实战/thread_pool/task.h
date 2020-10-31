#ifndef INC_TASK_H_
#define INC_TASK_H_ 

#include <iostream>
#include <functional> // bind function
#include <utility> // for forward

// 将函数和函数调用时所需的参数打包成一个任务对象
class Task{
public:
    template<typename Func_T, typename ...ARGS>
    Task(Func_T func, ARGS ...args) {
        this->func = std::bind(func, std::forward<ARGS>(args)...);
    }
    void run() {
        this->func();
        return ;
    }
    std::function<void()> func;
};

#endif // !INC_TASK_H_
