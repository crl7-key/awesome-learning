# C++设计模式之代理模式

* [代理模式](#代理模式)
* [AOP](#AOP)
## 代理模式
代理模式给某一个对象提供一个代理对象,并由代理对象控制对原对象的引用。通俗的来讲代理模式就是我们生活中常见的中介。

代理模式中通常有三个角色:**一个是抽象产品角色,一个是具体产品角色,另一个是代理产品角色**,这个代理产品角色的作用是**为了给原始的具体产品附加功能，需要注意的是代理模式附加的是原始类无关的功能,附加的如果是与原始类有关的功能那是装饰器模式**


代码实现如下:[proxy.cpp](proxy.cpp)
```c++
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
```
上述代码简单的使用了代理模式为某个类附加了一些额外的功能,平时在开发过程中如果想要为某个类附加一些额外功能时,可以考虑使用代理模式。

# AOP
`AOP`（`Aspect-Oriented Programming`，面向方面编程,也称切面编程），可以解决面向对象编程中的一些问题，是`OOP`的一种有益补充。面向对象编程中的继承是一种从上而下的关系，不适合定义从左到右的横向关系，如果继承体系中的很多无关联的对象都有一些公共行为，这些公共行为可能分散在不同的组件、不同的对象之中，通过继承方式提取这些公共行为就不太合适了。使用`AOP`还有一种情况是为了提高程序的可维护性，`AOP`将程序的非核心逻辑都“横切”出来，将非核心逻辑和核心逻辑分离，使我们能集中精力在核心逻辑上。`AOP`的作用在于分离系统中的各种关注点，将核心关注点和横切关注点分离开来。也可以理解为是一种代理模式。

代码实现：[AOP](static_proxy.cpp)
```c++
#include <iostream>
#include <ctime>
#include <sys/time.h>

// 检查类型是否存在非静态成员函数
#define HAS_MEMBER(member)                                                                                       \
    template <typename T, typename... Args>                                                                      \
    class has_member_##member {                                                                                 \
       private:                                                                                                  \
        template <typename U>                                                                                   \
        static auto Check(int) -> decltype(std::declval<U>().member(std::declval<Args>()...), std::true_type()); \
        template <typename U>                                                                                    \
        static std::false_type Check(...);                                                                       \
                                                                                                                 \
       public:                                                                                                   \
        enum { value = std::is_same<decltype(Check<T>(0)), std::true_type>::value };                             \
    };

HAS_MEMBER(Foo) 
HAS_MEMBER(Before)
HAS_MEMBER(After)

template<typename Func,typename ...Args>
class Aspect {
public:
     Aspect(Func&& f) : m_func(std::forward<Func>(f)) {}

    template<typename T>
    typename std::enable_if<has_member_Before<T, Args...>::value && has_member_After<T, Args...>::value>::type Invoke(Args&&... args, T&& aspect) {
        aspect.Before(std::forward<Args>(args)...); // 核心逻辑之前的切面逻辑
        m_func(std::forward<Args>(args)...);        // 核心逻辑
        aspect.After(std::forward<Args>(args)...);  // 核心逻辑之后的切面逻辑
    }

    template<typename T>
    typename std::enable_if<has_member_Before<T, Args...>::value && !has_member_After<T, Args...>::value>::type Invoke(Args&&... args, T&& aspect) {
        aspect.Before(std::forward<Args>(args)...); // 核心逻辑之前的切面逻辑
        m_func(std::forward<Args>(args)...);        // 核心逻辑
    }

    template<typename T>
    typename std::enable_if<!has_member_Before<T, Args...>::value && has_member_After<T, Args...>::value>::type Invoke(Args&&... args, T&& aspect){
        m_func(std::forward<Args>(args)...);        // 核心逻辑
        aspect.After(std::forward<Args>(args)...);  // 核心逻辑之后的切面逻辑
    }

    template<typename Head, typename... Tail>
    void Invoke(Args&&... args, Head&&headAspect, Tail&&... tailAspect) {
        headAspect.Before(std::forward<Args>(args)...);
        Invoke(std::forward<Args>(args)..., std::forward<Tail>(tailAspect)...);
        headAspect.After(std::forward<Args>(args)...);
    }

private:
    Func m_func; // 被织入的函数
};

// 让vs能正确识别出模板参数,因为各个编译器对变参的实现是有差异的
template<typename T> 
using identity_t = T;

// AOP的辅助函数，简化调用
template<typename... AP, typename... Args, typename Func>
void Invoke(Func&&f, Args&&... args) {
    Aspect<Func, Args...> asp(std::forward<Func>(f));
    asp.Invoke(std::forward<Args>(args)..., identity_t<AP>()...);
}


class TimeElapsedAspect {
public:
    void Before(int i) {
        m_lastTime = GetTime();
    }

    void After(int i) {
        std::cout <<"time used: "<< GetTime() - m_lastTime << std::endl;
    }

private:
    long long m_lastTime;

    long long GetTime() {
        struct timeval time;
        gettimeofday(&time,NULL);
        return static_cast<long long>(time.tv_sec * 1000 + static_cast<long long>(time.tv_usec / 1000));
    }
};

class LoggingAspect {
public:
    void Before(int i ) {
        std::cout << "start " << std::endl;
    }

    void After(int i) {
        std::cout << "end " << std::endl;
    }
};

void TestFunc(int i) {
    std::cout << "Function : " << i << std::endl;
}

int main(int argc, char const *argv[])
{
    Invoke<LoggingAspect,TimeElapsedAspect>(TestFunc,1); //  //织入方法
    std::cout << "-----------------------" << std::endl;

    Invoke<TimeElapsedAspect, LoggingAspect>(&TestFunc, 1);

    return 0;
}

```
通过`AOP`可以为某个函数前后编织切入一些方法，组成一个新的函数，这里也起到了代理作用，可以理解为一种静态代理。

**[⬆ 返回顶部](#Proxy)**