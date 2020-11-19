#include <iostream>

class Component {
public:
  virtual ~Component() {}

  virtual void Configuration() = 0;
};

class Product1Decorator : public Component {
public:
    Product1Decorator() {}
    Product1Decorator(Component* component) { m_component = component; }
    void Configuration() override {
        std::cout << "Product1Decorator::Configuration()" << std::endl;
        if (m_component) m_component->Configuration();
    }

private:
    Component* m_component;
};


class Product2Decorator : public Component {
public:
    Product2Decorator() {}
    Product2Decorator(Component* component) { m_component = component; }
    void Configuration() override {
        std::cout << "Product2Decorator::Configuration()" << std::endl;
        if (m_component) m_component->Configuration();
    }

  private:
  Component* m_component;
};

int main() {
  Component* component = new Product1Decorator();
  component = new Product2Decorator(component); // 暂时忽略内存泄漏
  component->Configuration();
  return 0;
}