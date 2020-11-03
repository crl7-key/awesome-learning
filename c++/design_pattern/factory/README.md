# C++设计模式之工厂模式
![](https://img.shields.io/badge/standard--readme-MIT-green?style=flat&logo=appveyor)   

## 目录
* [什么是工厂模式？](#什么是工厂模式？)
* [简单工厂模式](#简单工厂模式)
* [工厂方法模式](#工厂方法模式)
* [抽象工厂模式](#抽象工厂模式)

## 什么是工厂模式？
工厂模式是用来创建对象的一种最常用的设计模式。我们不暴露创建对象的具体逻辑,而是将逻辑封装在一个函数中,那么这个函数就可以被视为一个工厂。工厂模式根据抽象程度的不同可以分为:
- 简单工厂模式
- 工厂方法模式
- 抽象工厂模式

## 简单工厂模式
简单工厂模式就是把对象的创建放到一个专门的工厂类中,通过参数类型来创建不同的对象。工厂可以根据不同的需求生产出不同的产品。
```c++
#include <iostream>

typedef enum ProductType {
    TypeA,
    TypeB,
    TypeC
}PRODUCTTYPE;

class Product { // 产品基类
public:
    Product() {}
    ~Product() {}
    virtual void Show() = 0;
};

class ProductA: public Product { // 产品A
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

class ProductC: public Product { // 产品C
public:
    void Show() {
        std::cout << "ProductC::Show()" << std::endl;
    }
};


class SimpleFactory {
public:
    static Product* CreateProduct(PRODUCTTYPE type);
};

Product*SimpleFactory::CreateProduct(PRODUCTTYPE type) {
    switch (type)
    {
    case PRODUCTTYPE::TypeA:
        return new ProductA();
    case PRODUCTTYPE::TypeB:
        return new ProductB();
    case PRODUCTTYPE::TypeC:
        return new ProductC();
    }
}

int main(int argc, char const *argv[])
{
    ProductA* productA = static_cast<ProductA*>(SimpleFactory::CreateProduct(PRODUCTTYPE::TypeA));
    productA->Show();

    ProductB* productB = static_cast<ProductB*>(SimpleFactory::CreateProduct(PRODUCTTYPE::TypeB));
    productB->Show();

    ProductC* productC = static_cast<ProductC*>(SimpleFactory::CreateProduct(PRODUCTTYPE::TypeC));
    productC->Show();

    return 0;
}
```
通过上述代码可以看到简单工厂方法的优点,实现了对象的创建和使用逻辑分离,只需要传入不同的参数,就可以获得特定具体类的实例。即去除了与具体产品的依赖,屏蔽了对象的创建细节。但是简单工厂方法也有缺点,就是当增加了新的产品,就需要修改工厂类的逻辑,就需要修改工厂类的创建逻辑,如果产品类型较多,就可能造成工厂类逻辑过于复杂,不利于系统的维护,这种模式只适用于具体产品类型较少并且以后基本不会新加类型的场景，这样工厂业务逻辑就不会太过复杂。


## 简单工厂模式
为了解决上面简单工厂模式的缺点,进一步抽象出了工厂方法模式,工厂类不再负责所有产品的构建,每一个具体产品都有一个对应的工厂,这样在新加产品时就不会改动已有工厂类的创建逻辑。这些工厂也会抽象出一个抽象工厂。可以理解为有四种角色:抽象产品、具体产品、抽象工厂、具体工厂,其实就是把简单工厂模式中的工厂类做进一步的的抽象。
```c++
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
```
工厂模式提高类系统的可扩展性,完全符合开闭原则,当新加具体产品时,完全不会对已有系统有任何修改。当不知道以后会有多少具体产品时可以考虑使用工厂模式,因为不会降低现有系统的稳定性。但是它也有缺点，每当新加一个产品时,不仅需要新加一个对应的产品类,同时还需要新增加一个此产品对应的工厂.系统的复杂度比较高。


## 抽象工厂模式
在工厂方法中,每一个抽象产品都会有一个抽象工厂,这样新增加一个产品时都会新增加两个类,一个具体产品类,一个具体工厂类,我们可以考虑多个抽象产品对应一个抽象工厂,这样就有效的减少具体工厂类的个数.
```c++
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
```

**[⬆ 返回顶部](#目录)**