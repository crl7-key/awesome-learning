#ifndef INC_THREAD_POOL_H_
#define INC_THREAD_POOL_H_

#include "task.h"
#include <vector>
#include <thread>
#include <mutex>
#include <queue>

template<typename QueueType = std::queue<Task *>>
class ThreadPool{
public:
    // 在构造函数中新建 n 个线程，保存到 threads 动态数组
    ThreadPool(size_t n) {
        is_running = true; // 表示线程池处于工作状态
        for(int i = 0; i < n; ++i) {
            threads.push_back(
                new std::thread(
                    &ThreadPool::thread_worker,
                    this
                )
            );
        }
    }

    void thread_worker() {
        std::cout << "worker begin"  << std::endl;
        while(is_running) {
            Task* t = this->getOneTask(); // 获取任务
            if (t == nullptr) break; // 获取失败,break
            t->run();   // 执行任务
            delete t;
        }
        std::cout << "worker end"  << std::endl;
        return ;
    }

    Task *getOneTask() {
        // 进入临界区时加锁,保证多线程环境下资源访问安全性
        std::unique_lock<std::mutex> lock(m_mutex);
        // 等待任务
        while(is_running && tasks.empty()) m_cond.wait(lock); // 等待队列中被放入任务，或者线程池停止工作
        // 获取任务
        Task* t = nullptr;
        if(is_running) {
            t = tasks.front();
            tasks.pop();
        }
        return t;
    }

    void addOneTask(Task *t) {
        // 给临界区加锁
        std::unique_lock<std::mutex> lock(m_mutex);
        // 将计算任务放到计算队列中
        tasks.push(t);
        // 通知正在等待的工作线程
        m_cond.notify_one();
        return ;
    }

    // 在析构函数中负责销毁 n 个线程，调用 join 方法等待线程执行结束，然后调用delete方法释放线程
    ~ThreadPool() {
        do {
            // 条件变量的通知
            is_running = false; // 表示线程池即将被销毁要停止工作了
            std::unique_lock<std::mutex> lock(m_mutex);
            m_cond.notify_all();
        }while(0);
        
        for (int i = 0; i < threads.size(); i++) {
            threads[i]->join();  // 等待线程执行结束
            delete threads[i];  // 释放线程
        } 
        return ;
    }

private:
    std::vector<std::thread *> threads;
    std::mutex m_mutex;
    std::condition_variable m_cond;
    QueueType tasks;
    bool is_running; // 线程池是否还在继续运行
};
#endif // !INC_THREAD_POOL_H_