#include <iostream>

using namespace std;

class Product { // 产品基类
public:
    Product() {}
    virtual ~Product() {}
    virtual void Show() = 0;
};

class ProductA : public Product { // 产品A
public:
    void Show() override {
        std::cout << "ProductA::Show()" << std::endl;
    }
};

class ProductB : public Product { // 产品B
public:
    void Show() override {
        std::cout << "ProductB::Show()" << std::endl;
    }
};

class ProductC : public Product { // 产品C
public:
    void Show() override {
        std::cout << "ProductC::Show()" << std::endl;
    }
};

class Abstract {
public:
    Abstract() {}
    virtual ~Abstract() {}
    virtual void foo() {}
};

class ProductAAbstract : public Abstract { 
public:
    void foo() override {
        std::cout << "ProductAAbstract::foo()" << std::endl;
    }
};

class ProductBAbstract : public Abstract { 
public:
    void foo() override {
        std::cout << "ProductBAbstract::foo()" << std::endl;
    }
};

class ProductCAbstract : public Abstract { 
public:
    void foo() override {
        std::cout << "ProductCAbstract::foo()" << std::endl;
    }
};


class Factory {
public:
    virtual ~Factory() {}
    virtual Product* CreateProduct() = 0;
    virtual Abstract* CreateAbstract() = 0;
};


class ProductABaseFactory : public Factory { // 产品A工厂
public:
    Product* CreateProduct() override {
        return new ProductA();
    }
    Abstract* CreateAbstract() override {
        return new ProductAAbstract();
    }

};

class ProductBBaseFactory : public Factory { // 产品B工厂
public:
    Product* CreateProduct() override {
        return new ProductB();
    }
     Abstract* CreateAbstract() override {
        return new ProductBAbstract();
    }
};

class ProductCBaseFactory : public Factory { // 产品C工厂
public:
    Product* CreateProduct() override {
        return new ProductC();
    }
    Abstract* CreateAbstract() override {
        return new ProductCAbstract();
    }
};

int main(int argc, char const *argv[])
{
    Factory* factory = new ProductABaseFactory();
    Product* productA = factory->CreateProduct();
    Abstract* abstractA = factory->CreateAbstract();
    productA->Show();
    abstractA->foo();

    delete productA;
    delete abstractA;
    delete factory;

    factory = new ProductBBaseFactory();
    Product* productB = factory->CreateProduct();
    Abstract* abstractB = factory->CreateAbstract();
    productB->Show();
    abstractB->foo();

    delete productB;
    delete abstractB;
    delete factory;

    factory = new ProductCBaseFactory();
    Product* productC = factory->CreateProduct();
    Abstract* abstractC = factory->CreateAbstract();
    productC->Show();
    abstractC->foo();

    delete productC;
    delete abstractC;
    delete factory;

    return 0;
}
