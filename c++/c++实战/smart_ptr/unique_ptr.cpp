#include "shape.h"

template<typename T>
class unique_ptr {
public:
    explicit unique_ptr(
            T *ptr = nullptr) noexcept 
            : ptr_(ptr){}

    ~unique_ptr() noexcept {
        delete ptr_;
        ptr_ = nullptr;
    }

    T &operator*()const noexcept { return *ptr_; }
    
    T *operator->()const noexcept { return ptr_; }
    
    operator bool() const noexcept { return ptr_; }

    // unique_ptr(unique_ptr &&other) noexcept {
    //     ptr_ = other.release();
    // }

    unique_ptr &operator=(unique_ptr rhs) noexcept {
        rhs.swap(*this);
        return *this;
    }
    
    // 在拷贝构造函数中调用，释放原来指针的所有权
    T *release() noexcept {
        T *ptr = ptr_;
        ptr_ = nullptr;
        return ptr;
    }
    
    // 在赋值函数中调用
    void swap(unique_ptr &rhs) noexcept {
        using std::swap;
        swap(ptr_,rhs.ptr_); // 转移指针所有权
    }

    template<typename U>
    unique_ptr(<unique_ptr<U> &&other) noexcept {
    ptr_ = other.release();
}

private:
    T *ptr_;
};

template<typename T>
void swap(unique_ptr<T> &lhs, unique_ptr<T> &rhs) {
    lhs.swap(rhs);
}

int main()
{
     unique_ptr<shape> ptr1{create_shape(shape_type::circle)};
     // unique_ptr<shape> ptr2 {ptr1}; // error
     unique_ptr<shape> ptr2 {ptr1}; // error
     unique_ptr<shape> ptr2 {std::move(ptr1)};

     unique_ptr<shape> ptr3 {create_shape(shape_type::rectangle)};
     // ptr1 = ptr3; // error
     ptr1 = ptr3;
     ptr3 = std::move(ptr1);

     return 0;
}
