#ifndef INC_SHAPE_H_
#define INC_SHAPE_H_

#include <iostream>

enum class shape_type {
    circle,
    triangle,
    rectangle,
};

class shape {
public:
    shape() {
        std::cout << "shape() " << std::endl;
    }

    virtual void print() {
        std::cout << " shape print() " <<std:: endl;
    }

    virtual ~shape(){
        std::cout << " ~shape() " << std::endl;
    }
};

class circle : public shape {
public:
    circle() {
        std::cout << "circle() " << std::endl;
    }

    void print() {
        std::cout << "circle print() " << std::endl;
    }
    
    ~circle() {
        std::cout << "~circle() " << std::endl;
    }
};

class triangle : public shape {
public:
    triangle() {
        std::cout << "triangle() " << std::endl;
    }
    void print() {
        std::cout << "triangle print() " << std::endl;
    }
    ~triangle() {
        std::cout << "~triangle() " << std::endl;
    }
};

class rectangle : public shape {
public:
    rectangle() {
        std::cout << "rectangle() " << std::endl;
    }
    void print() {
        std::cout << "rectangle print() " << std::endl;
    }
    ~rectangle() {
        std::cout << "~rectangle() " << std::endl;
    }
};

// 使用多态，向上转换，如果返回值为shape,会存在对象切片问题
shape* create_shape(shape_type type) {
    switch (type) {
    case shape_type::circle:
        return new circle();
    case shape_type::triangle:
        return new triangle();
    case shape_type::rectangle:
        return new rectangle();
    default:
        return nullptr;
    }
}
#endif
