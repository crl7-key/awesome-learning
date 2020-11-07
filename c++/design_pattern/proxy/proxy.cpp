#include <iostream>

class Product {
public:
    virtual ~Product() {}
    virtual void Use() = 0;
};

class ConcreteProduct : public Product{
public:
    void Use() override {
        std::cout << "ConcreteProduct::Use()" << std::endl; 
    }
};

class ProductProxy : public Product {
public:
    ProductProxy() {
        product = new ConcreteProduct();
    }

    ~ProductProxy() {
        delete product;
        product = nullptr;
    }

    void Use() override {
        auto begin_use = []() {
            std::cout << "use product begin" << std::endl;
        };

        auto end_use = []() {
            std::cout << "use product end" << std::endl;
        };

        begin_use();

        product->Use();

        end_use();
    }

private:
    Product* product;
};

int main(int argc, char const *argv[])
{
    ProductProxy proxy;
    proxy.Use();
    return 0;
}
