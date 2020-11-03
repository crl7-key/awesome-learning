#include <iostream>

using namespace std;

typedef enum ProductType {
    TypeA,
    TypeB,
    TypeC
} PRODUCTTYPE;

class Product { // 产品基类
public:
    virtual void Show() = 0;
};

class ProductA : public Product { // 产品A
public:
    void Show() {
        std::cout << "ProductA::Show()" << std::endl;
    }
};

class ProductB : public Product { // 产品B
public:
    void Show() {
        std::cout << "ProductB::Show()" << std::endl;
    }
};

class ProductC : public Product { // 产品C
public:
    void Show() {
        std::cout << "ProductC::Show()" << std::endl;
    }
};

class SimpleFactory {
public:
    static Product *CreateProduct(PRODUCTTYPE type);
};

Product *SimpleFactory::CreateProduct(PRODUCTTYPE type) {
    switch (type)
    {
    case PRODUCTTYPE::TypeA:
        return new ProductA();
    case PRODUCTTYPE::TypeB:
        return new ProductB();
    case PRODUCTTYPE::TypeC:
        return new ProductC();
    default:
        return nullptr;
    }
}

// 使用模板解决简单工厂模式的缺陷
class Factory {
public:
    template <class T>
    static T *CreateProduct()
    {
        return new T();
    }
};

int main(int argc, char const *argv[])
{
    ProductA *productA = static_cast<ProductA *>(SimpleFactory::CreateProduct(PRODUCTTYPE::TypeA));
    productA->Show();

    ProductB *productB = static_cast<ProductB *>(SimpleFactory::CreateProduct(PRODUCTTYPE::TypeB));
    productB->Show();

    ProductC *productC = static_cast<ProductC *>(SimpleFactory::CreateProduct(PRODUCTTYPE::TypeC));
    productC->Show();

    return 0;
}
