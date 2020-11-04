#include <iostream>

class Prototype {
public:
    Prototype() {}
    virtual ~Prototype() {}
    
    virtual Prototype* Clone() = 0;

    virtual void Show() = 0;
};

class ConcretePrototype1: public Prototype {
public:
    Prototype* Clone() override {
        return new ConcretePrototype1();
    }

    void Show() override {
        std::cout << "ConcretePrototype1::Show()" << std::endl;
    }
};


class ConcretePrototype2: public Prototype {
public:
    Prototype* Clone() override {
        return new ConcretePrototype2();
    }

    void Show() override {
        std::cout << "ConcretePrototype2::Show()" << std::endl;
    }
};

int main(int argc, char const *argv[])  
{
    Prototype* prototype1 = new ConcretePrototype1();
    prototype1->Show();

    Prototype* prototype1_bak = prototype1->Clone();
    prototype1_bak->Show();

    Prototype* prototype2 = new ConcretePrototype2();
    prototype2->Show();

    Prototype* prototype2_bak = prototype2->Clone();
    prototype2_bak->Show();
    return 0;
}
