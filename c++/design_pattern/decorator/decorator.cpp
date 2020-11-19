#include <iostream>

// 抽象组件
class Component {
public:
    virtual ~Component() {}

    virtual void Configuration() = 0;
};

class Product1 : public Component {
public:
    void Configuration() override {
        std::cout << "Product1:: Configuration() " << std::endl;
    }
};

class Product2 : public Component {
public:
    void Configuration() override {
        std::cout << "Product2:: Configuration() " << std::endl;
    }
};

class Product3 : public Component {
public:
    void Configuration() override {
        std::cout << "Product1:: Configuration() " << std::endl;
        std::cout << "Product2:: Configuration() " << std::endl;
    }
};

int main(int argc, char const *argv[])
{
    Component* component = new Product3();
    component->Configuration();
    return 0;
}
