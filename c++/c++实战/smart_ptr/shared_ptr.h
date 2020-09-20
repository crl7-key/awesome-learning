#ifndef INC_SHARED_PTR_H
#define INC_SHARED_PTR_H

#include "shared_count.h"
#include <iostream>

template<typename T>
class shared_ptr {
public:

    // 由于模板的各个实例间并不天然就有friend关系，因而不能互访私有成员，需要显示声明
    template<typename U>
        friend class shared_ptr;

    // explicit作用:用于修饰只有一个参数的类构造函数 表明该构造函数是显示的, 而非隐式的,与之相对应的关键字为implicit，类构造函数默认情况下即声明为implicit(隐式)
    explicit shared_ptr(T *ptr = nullptr) noexcept
        :ptr_(ptr) {
            if (ptr) {
                shared_count_ = new shared_count();
            }
        }

    // 当最后一个shared_ptr再去删除对象与共享计数
    //  ptr 不为空且此时共享计数减为0的时候，再去删除
    ~shared_ptr() noexcept {
        std::cout << "~shared_ptr(): " << this << std::endl;
        if (ptr_ && !shared_count_->get_count()) {
            delete ptr_ ;
            delete shared_count_;
            ptr_ = nullptr;
            shared_count_ = nullptr;
        }
    }

    void swap(shared_ptr &rhs) noexcept {
        using std::swap;
        swap(ptr_,rhs.ptr_);
        swap(shared_count_,rhs.shared_count_);
    }

    // copy and swap 始终只有一个对象有管理这块空间的权限
    shared_ptr &operator=(shared_ptr rhs) noexcept {
        rhs.swap(*this);
        return *this;
    }

    shared_ptr(const shared_ptr &other) noexcept {
        std::cout << "shared_ptr(const shared_ptr &other) " << std::endl;
        ptr_ = other.ptr_;
        if (ptr_) {
            other.shared_count_->add_count();
            shared_count_ = other.shared_count_;
        }
    }

    // 拷贝构造模板
    template<typename U>
        shared_ptr(const shared_ptr<U> &other) noexcept {
            std::cout << "shared_ptr(const shared_ptr<U> &other)  " << std::endl;
            ptr_ = other.ptr_;
            if (ptr_) {
                other.shared_count_->add_count();
                shared_count_ = other.shared_count_;
                
            }
        }

    //移动构造
    template<typename U>
        shared_ptr(const shared_ptr<U> &&other) noexcept {
            std::cout << " shared_ptr(const shared_ptr<U> &&other) " << std::endl;
            ptr_ = other.ptr_;
            if (ptr_) {
                shared_count_ = other.shared_count_;
                other.ptr_ = nullptr;
                other.shared_count_ = nullptr;
            }
        }

    // 强制类型转换需要的构造函数模板
    template<typename U>
        shared_ptr(const shared_ptr<U> &other, T *ptr) noexcept {
            std::cout << "shared_ptr(const shared_ptr<U> &other, T *ptr) " << std::endl;
            ptr_ = ptr;
            if (ptr_) {
                other.shared_count_->add_count();
                shared_count_ = other.shared_count_;
            }
        }

    // 返回 shared_ptr所指向对象的引用计数
    long use_count() const noexcept {
        if (ptr_) {
            return shared_count_->get_count();
        }
        else {
            return 0;
        }
    }

    T *get()const noexcept {
        return ptr_;
    }
    // 重载 *运算符解引用 使其该类能使用*解引用
    T *operator*()const noexcept {
        return *ptr_;
    }
    // 重载 ->运算符指向对象成员
    T &operator->()const noexcept {
        return ptr_;
    }
    // 重载bool 像指针一样用在布尔表达式中 检查是否有关联的管理对象
    operator bool()const noexcept {
        return ptr_;
    }
private:
    T *ptr_;
    shared_count *shared_count_;
};

template<typename T>
void swap(shared_ptr<T> &lsh,shared_ptr<T> &rhs) noexcept {
    lsh.swap(rhs);
}

// static_cast 类型转换
template<typename T, typename U>
shared_ptr<T> static_pointer_cast(const shared_ptr<U> &other) noexcept {
    T *ptr = static_cast<T*>(other.get());
    return shared_ptr<T>(other,ptr);
}

// dynamic_cast 类型转换
template<typename T, typename U>
shared_ptr<T> dynamic_pointer_cast(const shared_ptr<U> &other) noexcept {
    T *ptr = dynamic_cast<T*>(other.get());
    return shared_ptr<T>(other,ptr);
}
// const_cast 类型转换
template<typename T, typename U>
shared_ptr<T> const_pointer_cast(const shared_ptr<U> &other) noexcept {
    T *ptr = const_cast<T*>(other.get());
    return shared_ptr<T>(other,ptr);
}

// reinterpret_cast 类型转换
template<typename T, typename U>
shared_ptr<T> reinterpret_pointer_cast(const shared_ptr<U> &other) noexcept {
    T *ptr = reinterpret_cast<T*>(other.get());
    return shared_ptr<T>(other,ptr);
}
#endif
