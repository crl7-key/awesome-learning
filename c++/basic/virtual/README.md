# 虚函数

`虚函数`是在基类中使用关键字`virtual`声明的函数。
```c++
class Base // 基类
{
public:
    virtual void foo() { //虚函数
        cout << "Base::foo()" << endl;
    }
};
```

## 目录
* [虚函数中的默认参数](#虚函数中的默认参数)
* [虚函数与多态](#虚函数与多态)
* [虚函数需要注意的地方](#虚函数需要注意的地方)
* [纯虚函数和抽象类](#纯虚函数和抽象类)

### 虚函数中的默认参数
 默认参数是静态绑定的,虚函数是动态绑定的。默认参数的使用需要看指针或者引用本身的类型，而不是对象的类型。
```c++
class Base 
{ 
public: 
    virtual void foo (int i = 10) { 
        cout << "Base::fun(), i = " << i << endl; 
    } 
}; 

class Derived : public Base 
{ 
public: 
    virtual void foo (int i = 20) { 
        cout << "Derived::fun(), i = " << i << endl; 
    } 
}; 

int main(int argc, char const *argv[])
{
    Derived obj;    // 派生类对象

    Base* p = &obj; // 基类指针指向派生类对象

    p->foo();      // 调用派生类同名函数 output: 20

    return 0;
}
```

### 虚函数与多态
虚函数的调用取决于指向或者引用的对象的类型，而不是指针或者引用自身的类型。
```c++
#include <iostream>

using namespace std;

class Base // 基类
{
public:
    virtual void foo() { //虚函数实现
        cout << "Base::foo()" << endl;
    }

};

// 派生类1
class Derived1 : public Base // 必须为公有继承，否则后面调用不到，class默认为私有继承
{
public:
    virtual void foo() { // 虚函数重写实现,子类中virtual 关键字可以没有
        cout << "Derived1::foo()" << endl;
    }
};

// 派生类2
class Derived2 : public Base // 必须为公有继承，否则后面调用不到，class默认为私有继承
{
public:
    virtual void foo() {    // 虚函数重写实现,子类中virtual 关键字可以没有
        cout << "Derived2::foo()" << endl;
    }
};

void globalFoo(Base* arr[],int n) {
    for(int i = 0; i < n ; ++i) {
        arr[i]->foo();
    }
}

int main()
{
    Base* arr[] = {new Derived1,new Derived2};

    globalFoo(arr,2);

    return 0;
}
```

### 虚函数需要注意的地方
- 静态函数不可以声明为虚函数，同时也不能被`const`和`volatile`关键字修饰  
    - `static`成员函数不属于任何类对象或类实例,所以即使给此函数加上`virutal`也是没有任何意义  
    - 虚函数依靠`vptr`和`vtable`来处理。`vptr`是一个指针,在类的构造函数中创建生成,并且只能用`this`指针来访问它,静态成员函数没有`this`指针,所以无法访问`vptr`。  
- 构造函数不可以声明为虚函数。构造函数除了`inline`和`explicit`之外,不允许使用其它任何关键字。   
- 析构函数可以声明为虚函数。如果我们需要删除一个指向派生类的基类指针时,应该把析构函数声明为虚函数。事实上,只要一个类有可能会被其它类所继承, 就应该声明虚析构函数(哪怕该析构函数不执行任何操作)。这是因为派生类如果在堆区申请空间,需要调用析构函数释放内存,但是如果是用基类的指针去释放,是释放不了的,就是只会调用基类的析构,而不会调用派生类的析构,会产生内存泄露,那么在基类的析构函数前加`virtual`成为虚析构,这个时候,释放的时候就会一起调用派生类的析构,就不会有内存泄露问题
```c++
class Base { 
public: 
    Base() { 
        cout << "Constructing Base \n"; 
    } 
    virtual ~Base() { 
        cout << "Destructing Base \n"; 
    }      
}; 

class Derived: public Base { 
public: 
    Derived() { 
        cout << "Constructing Derived \n"; 
    } 
    ~Derived() { 
        cout << "Destructing Derived \n"; 
    } 
}; 

int main() 
{ 
    Derived *obj = new Derived();   

    Base *p = obj; 

    delete p; // 调用派生类的析构 

    return 0; 
} 
``` 

- 通常类成员函数都会被编译器考虑是否进行内联。 但通过基类指针或者引用调用的虚函数必定不能被内联。 当然,实体对象调用虚函数或者静态调用时可以被内联,虚析构函数的静态调用也一定会被内联展开。
    - 虚函数可以是内联函数,内联是可以修饰虚函数的,但是当虚函数表现多态性的时候不能内联。
    - 内联是在编译器建议编译器内联,而虚函数的多态性在运行期,编译器无法知道运行期调用哪个代码,因此虚函数表现为多态性时（运行期）不可以内联。
    - `inline virtual`唯一可以内联的时候是：编译器知道所调用的对象是哪个类（如`Base::foo()`）,只有在编译器具有实际对象而不是对象的指针或引用时才会发生
```c++
class Base
{
public:
    inline virtual void foo(){
        cout << "I am Base\n";
    }
    virtual ~Base() {}
};

class Derived : public Base
{
public:
    inline void foo() { // 不写inline时隐式内联
        cout << "I am Derived\n";
    }
};

int main()
{
    // 此处的虚函数 foo()，是通过类（Base）的具体对象（obj）来调用的，编译期间就能确定了，所以它可以是内联的，但最终是否内联取决于编译器。 
    Base obj;
    obj.foo();

    // 此处的虚函数是通过指针调用的，呈现多态性，需要在运行时期间才能确定，所以不能为内联。  
    Base* p = new Derived();
    p->foo();

    // 因为Base有虚析构函数（virtual ~Base() {}），所以 delete 时，会先调用派生类（Derived）析构函数，再调用基类（Base）析构函数，防止内存泄漏。
    delete p;

    return 0;
} 
```

- 基类指针指向继承类对象，则调用继承类对象的函数；`int main()`必须声明为`Base`类的友元，否则编译失败。 编译器报错： p无法访问私有函数。 当然，把基类声明为`public`, 继承类为`private`，该问题就不存在了

```c++
class Base { 
private: 
    virtual void foo() { cout << "Base::foo()"; } 
    friend int main(); 
}; 

class Derived: public Base { 
public: 
    void foo() { cout << "Derived::foo()"; } 
}; 

int main() 
{ 
    Base* p = new Derived; 
    p->foo(); 
    return 0; 
}
```

### 纯虚函数和抽象类
C++中的纯虚函数(或抽象函数)是我们没有实现的虚函数,我们只需声明它,通过声明中赋值`0`来声明纯虚函数.
```c++
// 抽象类
class Base {
public: 
    virtual void foo() = 0; // 纯虚函数
};
```
如果类中有存纯虚函数的类叫抽象类,抽象类不能实例化对象.    
**注意**：  
- 如果派生类继承了抽象类,派生类如果不重写纯虚函数,那么这个派生类也是一个抽象类不能实例化对象,所以一般派生类需要重写纯虚函数
```c++
// Derived为抽象类,不能实例化对象
class Derived: public Base 
{ 
public: 

}; 
```
- 在抽象类中：在成员函数内可以调用纯虚函数,在构造函数和析构函数内部不能使用纯虚函数。
- 抽象类可以有构造函数
```c++
// 抽象类
class Base { 
protected: 
    int x; 
public: 
    virtual void foo() = 0; 
    Base(int i) { x = i; }  // 构造函数
}; 
// 派生类
class Derived: public Base 
{ 
private:
    int y; 
public: 
    Derived(int i, int j) : Base(i) { y = j; } // 构造函数
    void foo() { cout << "x = " << x << ", y = " << y; }
};
```

- 使用纯虚析构时析构函数一定要在类外定义
```c++
class Base {
public: 
    virtual void foo() = 0; // 纯虚函数

    virtual ~Base() = 0;    // 纯虚析构
};

Base::~Base() {
    cout << " Base::~Base()" << endl;
}
```


**[⬆ 返回顶部](#目录)**