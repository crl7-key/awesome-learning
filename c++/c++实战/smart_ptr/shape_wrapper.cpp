#include "shape.h"

class shape_wrapper {
public:
    explicit shape_wrapper(shape *ptr = nullptr): ptr_(ptr) {}

    ~shape_wrapper() {
        delete ptr_;
        ptr_ = nullptr;
    }

    shape *get()const {
        return ptr_;
    }

private:
        shape *ptr_;
};

void foo() {
    shape_wrapper ptr(create_shape(shape_type::circle));
    ptr.get()->print();
}

int main()
{
    shape* s = create_shape(shape_type::circle);
    s->print();
    delete  s;
    s = nullptr;

    foo();
    return 0;
}

