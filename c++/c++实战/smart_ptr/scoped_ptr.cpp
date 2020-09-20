#include "shape.h"

template<typename T>
class scoped_ptr
{
public:
    explicit scoped_ptr(T *ptr = nullptr ) noexcept : ptr_(ptr) {}

    ~scoped_ptr() noexcept {
        delete ptr_;
    }

    T &operator*() const noexcept {
        return *ptr_;
    }

    T *operator->()const noexcept {
        return ptr_;
    }

    operator bool()const noexcept {
        return ptr_;
    }

    T *get() const noexcept {
        return ptr_;
    }

    void reset(T *ptr = nullptr) noexcept {
        scoped_ptr(ptr).swap(*this);
    }

    void swap(scoped_ptr &rhs) noexcept {
        using std::swap;
        swap(ptr_,rhs.ptr_);
    }

private:
    T *ptr_;
    scoped_ptr(scoped_ptr const&);
    scoped_ptr &operator=(scoped_ptr const &);
};

template<typename T> 
void swap(scoped_ptr<T> &lhs, scoped_ptr<T> &rhs) noexcept {
    lhs.swap(rhs);
}

int main() 
{
    scoped_ptr<shape>  ptr1 {create_shape(shape_type::circle)};   
    // scoped_ptr<shape> ptr2 {ptr1};  //error 禁止拷贝

    return 0;
}

