#ifndef INC_SHARED_COUNT_H_
#define INC_SHARED_COUNT_H_

#include <atomic>
/*  引用计数:是计算机编程语言中的一种内存管理技术，
 *  是指将资源（可以是对象、内存或磁盘空间等等）的被引用次数保存起来，
 *  当被引用次数变为零时就将其释放的过程。
 **/

class shared_count{
public:

    //noexcept作用:告诉编译器，函数中不会发生异常
    //当创建一个对象的实例并在堆上申请内存时，对象的引用计数就为1
    shared_count() noexcept : count_(1){}

    ~shared_count(){}

    // 在其他对象中需要持有这个对象时，就需要把该对象的引用计数加1
    void add_count() noexcept {
        ++ count_;
    }

    // 需要释放一个对象时，就将该对象的引用计数减1，直至对象的引用计数为0，对象的内存会被立刻释放。
    long reduce_count() noexcept {
        return  -- count_;
    }
    // 获取计数
    long get_count()const noexcept {
        return count_; 
    }
private:
    //定义一个原子类型,防止数据竞争,同步多线程间的内存访问
    std::atomic<long> count_;
};
#endif

