# Smart_ptr 智能指针:straight_ruler:

使用指针可以简化资源的管理，从根本上消除资源(包括内存)泄露的可能性。智能指针的本质上就是`RAII`资源管理功能的自然展现。

## 目录
* [模版化和易用性](#模版化和易用性)  
* [拷贝构造和赋值](#拷贝构造和赋值)  
* [scoped_ptr](#scoped_ptr)   
* ["移动"指针](#"移动"指针)  
* [子类指向基类的转换](#子类指向基类的转换)  
* [shared_ptr之引用计数](#shared_ptr之引用计数) 
* [指针类型转换](#指针类型转换) 

一个简单的`shape_wrapper`类：

```c++
class shape_wrapper {
public:
  explicit shape_wrapper(
    shape* ptr = nullptr)
    : ptr_(ptr) {}
  ~shape_wrapper()
  {
    delete ptr_;
  }
  shape* get() const { return ptr_; }

private:
  shape* ptr_;
};
```

这个类可以完成智能指针的最基本功能：对超出作用域的对象释放。**但它缺了点东西:**  
- 这个类只适用于shape类  
- 该类对象的行为不够像指针  
- 拷贝该类对象会引发程序行为异常  

## 模版化和易用性
想让这个类能够包装任意类型的指针，可以将它变成一个类模板。模板使用很简单，在开头增加声明`template <typename T>`,把代码中的`shape`替换成模板参数`T`就可以了。在使用的时候把原来的`shape_wrapper`改成`smart_ptr<shape>`就行。

```c++
template <typename T>
class smart_ptr {
public:
  explicit smart_ptr(T* ptr = nullptr)
    : ptr_(ptr) {}
  ~smart_ptr()
  {
    delete ptr_;
  }
  T* get() const { return ptr_; }
private:
  T* ptr_;
};
```
目前这个smart_ptr的行为还是和指针有点差异：
- 它不能用 `*` 运算符解引用
- 它不能用 `->`运算符指向对象成员
- 它不能像指针一样用在布尔表达式里。

于是可以添加三个成员函数:
```c++

template <typename T>
class smart_ptr {
public:
  …
  T& operator*() const { return *ptr_; }
  T* operator->() const { return ptr_; }
  operator bool() const { return ptr_; }
};
```

## 拷贝构造和赋值

```c++
smart_ptr<shape> ptr1{create_shape(shape_type::circle)};
smart_ptr<shape> ptr2{ptr1};
```

对于上述使用的时候，拷贝该类对象会引发程序编译异常行为。最简单的办法就是禁止拷贝。 

```c++
template <typename T>
class smart_ptr {
  …
  smart_ptr(const smart_ptr&)
    = delete;
  smart_ptr& operator=(const smart_ptr&)
    = delete;
  …
};
```
也可以将其私有化`private`。

禁用这两个函数非常简单，但却解决了一种可能出错的情况。否则，`smart_ptr ptr2{ptr1};` 在编译时不会出错，但在运行时却会有未定义行为——**由于会对同一内存释放两次，通常情况下会导致程序崩溃。**  

我们是不是可以考虑在拷贝智能指针时把对象拷贝一份？不行，通常人们不会这么用，因为**使用智能指针的目的就是要减少对象的拷贝**。何况，虽然我们的指针类型是`shape`，但实际指向的却应该是`circle`或`triangle`之类的对象。在 C++ 里没有像`Java`的`clone`方法这样的约定；**一般而言，并没有通用的方法可以通过基类的指针来构造出一个子类的对象来**。  

那么可以**在拷贝时转移指针的所有权**，大致实现如下:

```c++
template <typename T>
class smart_ptr {
    explict smart_ptr(
            T *ptr = nullptr) noexcept
            : ptr_(ptr) {}

    ~smart_ptr() noexcept {
        delete ptr_;
    }
	// 返回值为T&，允许*ptr=10操作
    T &operator*() const noexcept { return *ptr_; }

    T *operator->() const noexcept { return ptr_; }

    operator bool() const noexcept { return ptr_; }

    T *get() const noexcept { return ptr_; }

    // 拷贝构造,被复制时释放原来指针的所有权,交给复制方  
    smart_ptr(smart_ptr& other) noexcept {
        ptr_ = other.release();
    }

    // copy and swap
    smart_ptr& operator=(smart_ptr& rhs) noexcept {
        smart_ptr(rhs).swap(*this);
        return *this;
    }

    // 在拷贝构造函数中，调用release 释放原来的指针的所有权
    T* release() noexcept {
        T* ptr = ptr_;
        ptr_ = nullptr;
        return ptr;
    }
    // 在赋值函数中，拷贝构造产生一个临时对象并调用swap来交换对指针的所有权
    void swap(smart_ptr& rhs) noexcept {
        using std::swap;
        swap(ptr_, rhs.ptr_); // 转移指针所有权
    }
private:
    T *ptr_;
};

template<class T>
void swap(smart_ptr<T>&lhs, smart_ptr<T>& rhs) noexcept {
    lhs.swap(rhs);
}

int main()
{
    smart_ptr<shape> ptr1 {create_shape(shape_type::circle)};
    smart_ptr<shape> ptr2 {ptr1};

    if (ptr1.get() == nullptr && ptr2.get()) {
        cout << "拷贝构造: ptr1 释放了所有权，ptr2 获得了所有权" << endl;
    }

    ptr1 = ptr1;

    smart_ptr<shape> ptr3 {create_shape(shape_type::rectangle)};
    ptr1 = ptr3;

    if (ptr3.get() == nullptr && ptr1.get()) {
        cout << "赋值操作: 始终只有一个对象管理一个区块，ptr3释放了所有权，ptr1 获得了所有权" << endl;
    }
    return 0;
}
```

上面的代码的惯用法保证了强异常安全性：赋值分为拷贝构造和交换两步，异常只可能在第一步发生；而第一步如果发生异常的话，`this`对象完全不受任何影响。无论拷贝构造成功与否，结果只有赋值成功和赋值没有效果两种状态，而不会发生因为赋值破坏了当前对象的这种场景。
但是**`auto_ptr`在`C++17`时已经被正式从 C++ 标准里删除了。
** 上面的实现的最大问题就是，**它的行为会让程序员非常容易犯错。一不小心把它传递给另一个smart_ptr,你就不再拥有这个对象了。**

## scoped_ptr

针对这个问题，在C++11标准出来之前，C++98标准中都一直只有一个智能指针`auto_ptr`，我们知道，这是一个失败的设计。它的本质是**管理权的转移**，这有许多问题。而这时就有一群人开始扩展C++标准库的关于智能指针的部分，他们组成了`boost社区`，他们负责`boost库`的开发和维护。其目的是为C++程序员提供免费的、同行审查的、可移植的程序库。`boost`库可以和`C++标准库`完美的共同工作，并且为其提供扩展功能。现在的**C++11标准库**的智能指针很大程度上“借鉴”了`boost`库。

`boost::scoped_ptr`属于`boost`库，定义在`namespace boost`中，包含头文件`#include<boost/smart_ptr.hpp>` 可以使用。`scoped_ptr`跟`auto_ptr`一样，可以方便的管理单个堆内存对象，特别的是，`scoped_ptr`独享所有权，避免了`auto_ptr`恼人的几个问题。

`scoped_ptr`是一种简单粗暴的设计，它本质就是**防拷贝，避免出现管理权的转移**。这是它的最大特点，所以**它的拷贝构造函数和赋值运算符重载函数都只是声明而不定义**，而且为了防止有的人在类外定义，所以将函数声明为`private`。但这也是它最大的问题所在，就是**不能赋值拷贝**，也就是说功能不全。但是这种设计比较高效、简洁。没有`release()`函数，不会导致先前的内存泄露问题。

```c++
template<typename T>
class scoped_ptr
{
public:
    explicit scoped_ptr(T *ptr = nullptr ) noexcept : ptr_(ptr) {}

    ~scoped_ptr() noexcept {
        delete ptr_;
    }

    T &operator*() const noexcept {
        return *ptr_;
    }

    T *operator->()const noexcept {
        return ptr_;
    }

    operator bool()const noexcept {
        return ptr_;
    }

    T *get() const noexcept {
        return ptr_;
    }

    void reset(T *ptr = nullptr) noexcept {
        scoped_ptr(ptr).swap(*this);
    }

    void swap(scoped_ptr &rhs) noexcept {
        using std::swap;
        swap(ptr_,rhs.ptr_);
    }

private:
    T *ptr_;
    scoped_ptr(scoped_ptr const&);
    scoped_ptr &operator=(scoped_ptr const &);
};

template<typename T> 
void swap(scoped_ptr<T> &lhs, scoped_ptr<T> &rhs) noexcept {
    lhs.swap(rhs);
}
```

## "移动"指针

```c++
template<typename T>
class unique_ptr {
public:
    explicit unique_ptr(
            T *ptr = nullptr) noexcept 
            : ptr_(ptr){}

    ~unique_ptr() noexcept {
        delete ptr_;
    }

    T &operator*()const noexcept { return *ptr_; }
    
    T *operator->()const noexcept { return ptr_; }
    
    operator bool() const noexcept { return ptr_; }

    unique_ptr(unique_ptr &&other) noexcept {
        ptr_ = other.release();
    }

    unique_ptr &operator=(unique_ptr rhs) noexcept {
        rhs.swap(*this);
        return *this;
    }
    
    // 在拷贝构造函数中调用，释放原来指针的所有权
    T *release() noexcept {
        T *ptr = ptr_;
        ptr_ = nullptr;
        return ptr;
    }
    
    // 在赋值函数中调用
    void swap(unique_ptr &rhs) noexcept {
        using std::swap;
        swap(ptr_,rhs.ptr_); // 转移指针所有权
    }

private:
    T *ptr_;
};

template<typename T>
void swap(unique_ptr<T> &lhs, unique_ptr<T> &rhs) {
    lhs.swap(rhs);
}
```
上述修改处简单的使用"移动"来改善了其行为
- 把拷贝构造函数中的参数类型`smart_ptr&`改成了`smart_ptr&&`；现在它成了移动构造函数。  
- 把赋值函数中的参数类型`smart_ptr&`改成了`smart_ptr`，在构造参数时直接生成新的智能指针，从而不再需要在函数体中构造临时对象。现在赋值函数的行为是移动还是拷贝，完全依赖于构造参数时走的是移动构造还是拷贝构造。  

根据C++的法则，**如果提供来移动构造函数而没有手动提供拷贝构造函数，那么后者自动被禁用。** 于是得到以下输出:

```c++
int main()
{
  unique_ptr<shape> ptr1{create_shape(shape_type::circle)};
  // unique_ptr<shape> ptr2{ptr1};             // 编译error
  unique_ptr<shape> ptr3;
  // ptr3 = ptr1;                             // 编译error
  ptr3 = std::move(ptr1);                     // ok，可以
  unique_ptr<shape> ptr4{std::move(ptr3)};    // ok，可以
}
```
这也是C++11的`unique_ptr`的基本行为


## 子类指向基类的转换

一个`circle*`是可以隐式转换成`shape*`,但是上面的`unique_ptr<circle>`却无法自动转换成`unique_ptr<shape>`。

- 当我们只是在原有的移动构造上面添加`template<typename U> ,此时情况是移动构造变为带模板的移动构造，可以进行子类指向基类的转换，但是与移动构造相关调用的是默认移动构造函数，除非是子类向基类的转换，才会调用带模板的移动构造。  
- 六个特殊的成员函数其生成规则如下：  
    - 默认构造函数，生成规则和C++98一样，在用户没有声明自定义的构造函数的时候并且编译期需要的时候生成。  
    - 析构函数，生成规则和C++98一样，在C++11中有点不同的是，析构函数默认是noexcept。  
    - 拷贝构造函数，用户自定义了移动操作会导致不生成默认的拷贝构造函数，其它和C++98的行为一致。  
    - 拷贝赋值操作符，用户自定义了移动操作会导致不生成默认的拷贝赋值操作，其它和C++98的行为一致。  
    - 移动构造函数和移动赋值操作符，仅仅在没有用户自定义的拷贝操作，移动操作和析构操作的时候才会生成。  
    - 当类中含有特殊成员函数变为模板特殊成员函数的时候,此时不满足上述生成规则  

```c++
int main() {
    unique_ptr<shape> ptr1 {create_shape(shape_type::circle)};
    unique_ptr<shape> ptr2 {ptr1};  // 由于带模板的移动构造函数引发编译器会默认生成拷贝构造
    if (ptr1.get() != nullptr)      // bitwise copy 此时ptr1不为NULL
        ptr2.get()->print();

    unique_ptr<shape> ptr2 {std::move(ptr1)};              // 调用的是默认的移动构造,而不是带模板的移动构造 bitwise move
    if (ptr2.get() != nullptr && ptr1.get() != nullptr)   // ptr1 不为空
        ptr2.get()->print();

    unique_ptr<shape> ptr3{create_shape(shape_type::rectangle)};
    ptr1 = ptr3;            // ok  根据形参先调用默认拷贝,再调用拷贝赋值
    ptr3 = std::move(ptr1); // ok 根据形参先调用默认移动构造，而不是带参数的移动构造,再调用移动赋值
    unique_ptr<shape> ptr4(std::move(new circle));  // ok 调用带模板的移动构造
}
```

- 移动构造与带模板的移动构造同时存在，可以完成子类向基类的转换，此时是满足上述生成规则，此时不会生成拷贝函数。  

```c++
int main() {
    unique_ptr<shape> ptr1 {create_shape(shape_type::circle)};
    // unique_ptr<shape> ptr2{ptr1}; // error
    unique_ptr<shape> ptr2 {std::move(ptr1)};    // ok
    if (ptr2.get() != nullptr && ptr1.get() == nullptr)
        ptr2.get()->print();

    unique_ptr<shape> ptr3 {create_shape(shape_type::rectangle)};
    // ptr1 = ptr3;    // error
    ptr3 = std::move(ptr1); // ok
    // unique_ptr<circle> ptr4 {create_shape(shape_type::circle)};  // error 因为create_shape返回的是shape 不能基类转子类
    unique_ptr<circle> ptr4 {new circle()};
    unique_ptr<shape> ptr5(std::move(ptr4));  // ok unique_ptr<circle>转unique_ptr<circle>
```

## shared_ptr之引用计数

`unique_ptr`算是一种较为安全的智能指针了。但是，一个对象只能被单个`unique_ptr`所拥有，这显然不能满足所有使用场合的需求。一种常见的情况是，多个智能指针同时拥有一个对象；当它们全部都失效时，这个对象也同时会被删除。  

`unique_ptr`与`shared_ptr`的区别:
- `unique_ptr`对象创建后,获取到内存资源,该对象是唯一的,不能通过赋值等将自身的资源管理赋予给其它对象  
- `shared_ptr`支持多个智能指针同时管理一段内存,在共享同一对象时也需要同时共享同一个计数,当最后一个指向对象（和共享计数）的`shared_ptr`析构时，它需要删除对象和共享计数。  

共享计数的实现:  

```c++
class shared_count{
public:

    // noexcept作用:告诉编译器，函数中不会发生异常
    // 当创建一个对象的实例并在堆上申请内存时，对象的引用计数就为1
    shared_count() noexcept : count_(1){}

    ~shared_count(){}

    // 在其他对象中需要持有这个对象时，就需要把该对象的引用计数加1
    void add_count() noexcept {
        ++ count_;
    }

    // 需要释放一个对象时，就将该对象的引用计数减1，直至对象的引用计数为0，对象的内存会被立刻释放。
    long reduce_count() noexcept {
        return  -- count_;
    }
    // 获取计数
    long get_count()const noexcept {
        return count_; 
    }
private:
    // 定义一个原子类型,防止数据竞争,同步多线程间的内存访问
    std::atomic<long> count_;
};
```

引用计数智能指针实现:

```c++
template<typename T>
class shared_ptr {
public:
    explicit shared_ptr(
            T *ptr = nullptr) noexcept
            : ptr_(ptr) {
        if (ptr) {
            shared_count_ = new shared_count();
        }
    }

    // 当最后一个shared_ptr再去删除对象与共享计数
    // ptr_不为空且此时共享计数减为0的时候,再去删除
    ~shared_ptr() noexcept {
        if(ptr_&&!shared_count_->reduce_count()) {
            delete ptr_;
            delete shared_count_;
            ptr_ = nullptr;
        }
    }
	
    void swap(shared_ptr &rhs) noexcept {
        using std::swap;
        swap(ptr_, rhs.ptr_);   
        swap(shared_count_,rhs.shared_count_);
    }

private:
    T *ptr_;
    shared_count *shared_count_;
};

template<typename T>
void swap(shared_ptr<T> &lhs, shared_ptr<T> &rhs) noexcept {
    lhs.swap(rhs);
}
```

赋值函数可以和前面的一样,编译器可以根据调用来决定是调拷贝构造还是移动构函数:  

```c++
// copy and swap  始终只有一个对象有管理这块空间的权限
shared_ptr &operator=(shared_ptr rhs) noexcept {
    rhs.swap(*this);
    return *this;
}
```

拷贝构造和移动构造函数是需要更新:  
除复制指针之外，对于拷贝构造的情况，我们需要在指针非空时把引用数加一，并复制共享计数的指针。对于移动构造的情况，我们不需要调整引用数，直接把`other.ptr_`置为空，认为`other`不再指向该共享对象即可。  

```c++
  shared_ptr(const shared_ptr& other) noexcept{
    ptr_ = other.ptr_;
    if (ptr_) {
      other.shared_count_->add_count();
      shared_count_ = other.shared_count_;
    }
  }

  template <typename U>
  shared_ptr(const shared_ptr<U>& other) noexcept{
    ptr_ = other.ptr_;
    if (ptr_) {
      other.shared_count_->add_count();
      shared_count_ = other.shared_count_;
    }
  }

  template <typename U>
  shared_ptr(shared_ptr<U>&& other) noexcept{
    ptr_ = other.ptr_;
    if (ptr_) {
      shared_count_ = other.shared_count_;
      other.ptr_ = nullptr;
      other.shared_count_ = nullptr;
    }
  }
```

上面的代码有个问题：它不能正确编译。编译器会报错，像:  
> fatal error: ‘ptr_’ is a private member of ‘shared_ptr’  

错误原因是**模板的各个实例间并不天然就有`friend`关系**，因而不能互访私有成员`ptr_`和`shared_count_`。我们需要在`shared_ptr`的定义中显式声明:  

```c++
  template <typename U>
  friend class shared_ptr;
```

此外，在当前引用计数实现中，我们应该删除release释放所有权函数，编写一个返回引用计数值的函数。  

```c++
  long use_count() const {
    if (ptr_) {
      return shared_count_->get_count();
    } 
    else {
      return 0;
    }
  }
```
## 指针类型转换
对应于`C++`里的不同的类型强制转换:  

- static_cast  
    - 可以对内置的数据类型转换,不保证安全，需要人为的控制，对于发生继承关系的两个类，子类转基类的指针是安全的,基类转子类的指针不安全的,对于没有继承关系的两个类,它们的指针之间不能转换  
- dynamic_cast  
    - 不能对内置的数据类型进行转换,一般用来有继承关系的类之间转换,对于子类转基类安全可以转,基类转子类不可以转换,系统认为如果发生了多态,子类和基类之间的转换总是安全的
- const_cast  
    - 一般用来`const`修饰的指针或引用和没有`const`修饰的指针或引用之间的转换,`(const int b ; int  a = const_cast<int>(b)  这种是不可以的)`
- reinterpret_cast  
    - 一般不推荐使用,不安全,什么类型都可以转


智能指针需要实现类似的函数模板。实现本身并不复杂，但为了实现这些转换，我们需要添加构造函数，允许在对智能指针内部的指针对象赋值时，使用一个现有的智能指针的共享计数  

```c++
  template <typename U>
  smart_ptr(const smart_ptr<U>& other, T* ptr) noexcept {
    ptr_ = ptr;
    if (ptr_) {
      other.shared_count_->add_count();
      shared_count_ = other.shared_count_;
    }
  }
```

在上述`unique_ptr`处实现了子类向基类的转换，但是却没有实现基类向子类的转换，例如：:`unique_ptr<circle>`转`unique_ptr<shape>`。
实现这种，需要使用`dynamic_cast`
```c++
template<typename T, typename U>
shared_ptr<T> dynamic_pointer_cast(const shared_ptr<U> &other) noexcept {
    T *ptr = dynamic_cast<T *>(other.get());
    return shared_ptr<T>(other, ptr);
}
```

其它类型强制转换也是如此。


**[⬆ 返回顶部](#目录)**
