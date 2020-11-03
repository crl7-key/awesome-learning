#include <iostream>
#include <array>

class Product {
public:
    void SetPartFirst(int value) {
        this->first = value;
        flag[0] = true;
    }

    void SetPartSecond(int value) {
        if (!flag[0]) return;
        this->second = value;
        flag[1] = true;
    }

    void SetPartThird(int value) {
        if (!flag[0] || !flag[1]) return;
        this->third = value;
        flag[2] = true;
    }

    bool IsOk() {
        return flag[0] && flag[1] && flag[2];
    }
private:
    std::array<bool,3> flag;
    int first;
    int second;
    int third;
};

class AbstractBuilder {
public:
    AbstractBuilder() {}
    virtual ~AbstractBuilder() {}

    virtual void BuildFirst() = 0;
    virtual void BuildSecond() = 0;
    virtual void BuildThird() = 0;
    virtual Product* GetProduct() = 0;
};

class ConcreteBuilder : public AbstractBuilder {
public:
    ConcreteBuilder() {
        this->product = new Product();
    }

    ~ConcreteBuilder() {
        delete this->product;
    }

    void BuildFirst() {
        this->product->SetPartFirst(1);
    }

    void BuildSecond() {
        this->product->SetPartSecond(2);
    }

    void BuildThird() {
        this->product->SetPartThird(3);
    }

    Product* GetProduct() {
        return this->product;
    }

private:
    Product* product;
};

class Director {
public:
    Director(AbstractBuilder* builder) {
        this->builder = builder;
    }

    ~Director() {}

    Product* Construct() {
        this->builder->BuildFirst();
        this->builder->BuildSecond();
        this->builder->BuildThird();
        return this->builder->GetProduct();
    }
private:
    AbstractBuilder* builder;
};

int main(int argc, char const *argv[])
{
    AbstractBuilder* builder = new ConcreteBuilder();
    Director* director = new Director(builder);
    Product* product = director->Construct();

    std::cout << "product is " << product->IsOk() << std::endl;
    return 0;
}
