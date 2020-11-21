#include <iostream>

class Component {
public:
    virtual ~Component() {}

    virtual  void foo() = 0;
};

class Product : public Component {
public:
    void foo() {
        std::cout << "Product::foo()" << std::endl;
    }
};

class ProductDecorator : public Component {
public:
    ProductDecorator(){}
    ProductDecorator(Component* component) {
        this->component = component;
    }
    
    void foo() {
        // 功能增强的代码
        std::cout << "start" << std::endl;
        this->component->foo();
        // 功能增强的代码
        std::cout << "end " << std::endl;
    }

private:
    Component* component;
};

int main(int argc, char const *argv[])
{
    Component* component = new Product();
    component = new ProductDecorator(component);

    component->foo();

    return 0;
}
