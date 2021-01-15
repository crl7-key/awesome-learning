#include <iostream>

// 类适配器：基于继承
class Target { // 客户期望的接口，可以使具体或抽象的类，也可以是接口
public:
    virtual void foo1() {
        std::cout << "Target::foo1()" << std::endl;
    }

    virtual void foo2() {
        std::cout << "Target::foo2()" << std::endl;
    }

    virtual void fooc() {
        std::cout << "Target::fooc()" << std::endl;
    }
    virtual ~Target(){}
};

class Adaptee { // 需要适配的类
public:
    Adaptee() {
        std::cout << "Adaptee()" << std::endl;
    }

    void fooa() {
        std::cout << "Adaptee::fooa()" << std::endl;
    }

    void foob() {
        std::cout << "Adaptee::foob()" << std::endl;
    }
    
    void fooc() {
        std::cout << "Adaptee::fooc()" << std::endl;
    }
};

class Adaptor : public Adaptee ,public Target { // 将需要适配的类转换成一组符合targe接口定义的接口
public:
     Adaptor(Adaptee* adaptee,Target* target) : m_adaptee(adaptee),m_target(target) {     
    }
    void foo1() {
        m_adaptee->fooa();
    }

    void foo2() {
        // 重新实现foo2
    }

    void fooc() {
        m_adaptee->fooc();
        m_target->fooc();
    }
    
private:
    Adaptee* m_adaptee;
    Target* m_target;
};


int main(int argc, const char** argv) 
{
    Target* target = new Target;

    Adaptee* adaptee = new Adaptee;

    Adaptor* adaptor = new Adaptor(adaptee,target);
    adaptor->foo1();
    adaptor->foo2();
    adaptor->fooc();

    delete adaptor;
    adaptor = nullptr;
    delete adaptee;
    adaptee = nullptr;
    delete target;
    target = nullptr;

    return 0;
}