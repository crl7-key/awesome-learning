#include <iostream>


// Implement（实现类接口）：定义实现类的接口，这个接口不一定要与 Abstraction 的接口完全一致，事实上这两个接口可以完全不同。
class Implement
{
public:
    virtual ~Implement() {}
    virtual void OperationImplement() = 0;
};


// ConcreteImplement(具体实现类):实现了 Implement 定义的接口，在不同的 ConcreteImplement 中提供基本操作的不同实现
class ConcreteImplementA : public Implement {
public:
    ConcreteImplementA() {
        std::cout << "ConcreteImplementA::ConcreteImplementA()" << std::endl;
    }

    void OperationImplement() override {
        std::cout << "ConcreteImplementA::OperationImplement()" << std::endl;
    }

};


class ConcreteImplementB : public Implement {
public:
    ConcreteImplementB() {
        std::cout << "ConcreteImplementB::ConcreteImplementB()" << std::endl;
    }

    void OperationImplement()override {
         std::cout << "ConcreteImplementB::OperationImplement()" << std::endl;
     }
    
};


// 用于定义抽象类的接口，并且维护一个指向 implement 实现类的指针。它与 implement 之间具有关联关系。
class Abstraction {
public:
    Abstraction(Implement* implement) : m_implement(implement) {}

    virtual ~Abstraction() {}

    virtual void Operation() {
       
    }

protected:
    Implement* m_implement;
};


// 扩充由 Abstraction 定义的接口，在 ExtendedAbstraction 中可以调用在 implement 中定义的业务方法。
class ExtendedAbstraction : public Abstraction {
public:
    ExtendedAbstraction(Implement* implement):Abstraction(implement) {}

    void Operation() override{
       this->m_implement->OperationImplement();
    }
};


int main(int argc, char const *argv[])
{
    Implement* implement = new ConcreteImplementA;
    implement->OperationImplement();
    std::cout << std::endl;
    Abstraction* abstraction = new Abstraction(implement);
    abstraction->Operation();
    delete implement;
    implement = nullptr;
    delete abstraction;
    abstraction = nullptr;
    std::cout << std::endl;

    implement = new ConcreteImplementB;
    implement->OperationImplement();
    std::cout << std::endl;
    abstraction = new ExtendedAbstraction(implement);
    abstraction->Operation();

    delete implement;
    implement = nullptr;
    delete abstraction;
    abstraction = nullptr;

    return 0;
}
