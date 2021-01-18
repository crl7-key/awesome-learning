#include <iostream>

class Color {
public:
    virtual ~Color() {};

    virtual void show() = 0; 
};

class Red : public Color {
public:
    void show() {
        std::cout << "Red::show()" << std::endl;
    }
};

class Blue : public Color {
public:
    void show() {
        std::cout << "Blue::show()" << std::endl;
    }
};

class Shape {
public:
    Shape(Color *color):m_color(color) {}

    virtual ~Shape(){}

    virtual void Operation() = 0;  

protected:
    Color* m_color;
};

class ExtendedShape : public Shape {
public:
    ExtendedShape(Color *color) : Shape(color) {}

    void Operation() {
        this->m_color->show();
    }
};


int main(int argc, char const *argv[])
{

    Color* color = new Red;
    Shape* shape = new ExtendedShape(color);
    shape->Operation();   

    delete shape;
    shape = nullptr;

    delete color;
    color = nullptr;

    color = new Blue;
    shape = new ExtendedShape(color);
    shape->Operation();

    delete shape;
    shape = nullptr;

    delete color;
    color = nullptr;

    return 0;
}
