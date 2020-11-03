#include <iostream>

using namespace std;

typedef enum ProductType {
    TypeA,
    TypeB,
    TypeC
} PRODUCTTYPE;

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


class Factory {
public:
    virtual ~Factory() {}
    virtual Product* CreateProduct() = 0;
};


class ProductABaseFactory : public Factory { // 产品A工厂
public:
    Product* CreateProduct() override {
        return new ProductA();
    }
};

class ProductBBaseFactory : public Factory { // 产品B工厂
public:
    Product* CreateProduct() override {
        return new ProductB();
    }
};

class ProductCBaseFactory : public Factory { // 产品C工厂
public:
    Product* CreateProduct() override {
        return new ProductC();
    }
};

int main(int argc, char const *argv[])
{
    Factory* factory;
    PRODUCTTYPE product_type = PRODUCTTYPE::TypeA;
    switch (product_type)
    {
    case PRODUCTTYPE::TypeA:
       factory = new ProductABaseFactory();
    case PRODUCTTYPE::TypeB:
       factory = new ProductBBaseFactory();
    case PRODUCTTYPE::TypeC:
        factory = new ProductABaseFactory();
    }
    Product* productA = factory->CreateProduct();
    productA->Show();

    delete factory;
    delete productA;

    factory = new ProductBBaseFactory();
    Product* productB = factory->CreateProduct();
    productB->Show();

    delete factory;
    delete productB;

    factory = new ProductCBaseFactory();
    Product* productC = factory->CreateProduct();
    productC->Show();

    delete factory;
    delete productC;

    return 0;
}
