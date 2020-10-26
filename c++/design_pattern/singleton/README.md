# C++设计模式之单例模式

## 目录
* [单例的介绍](#单例的介绍)
* [单例的应用场景](#单例的应用场景)
* [单例的优点与缺点](#单例的优点与缺点)
* [基础版本的单例实现](#基础版本的单例实现)
* [懒汉模式与饿汉模式](#懒汉模式与饿汉模式)  
* [多线程加锁](#多线程加锁) 
* [双重检查锁模式](#双重检查锁模式) 
* [自动回收](#自动回收) 
* [最推荐的懒汉式单例](#最推荐的懒汉式单例) 

### 单例的介绍
单例模式主要解决一个全局使用的类频繁的创建和销毁的问题。单例模式下可以确保某`一个类只有一个实例`，而且自行实例化并向整个系统提供这个实例。
单例模式有三个要素：
- 某个类只能有一个实例
- 它必须自行创建这个实例
- 它必须自行向整个系统提供这个实例,即全局变量的特点.

### 单例的应用场景
- 要求生产唯一序列号。  
- `WEB`中的计数器,不用每次刷新都在数据库里加一次,用单例先缓存起来。  
- 创建的一个对象需要消耗的资源过多,比如`I/O`与数据库的连接等。  


### 单例的优点与缺点
优点：
- 在内存里只有一个实例,减少了内存的开销,尤其是频繁的创建和销毁实例（比如管理学院首页页面缓存）。
- 避免对资源的多重占用（比如写文件操作）。    

缺点：没有接口,不能继承,与单一职责原则冲突,一个类应该只关心内部逻辑,而不关心外面怎么样来实例化。  

### 基础版本的单例实现

一般创建唯一实例的步骤:
- 将默认的构造函数私有化,这样就不能利用默认构造函数创建出普通的对象
- 在类中创建出唯一的对象,`new`出一个对象，并且将对象设置为`static`
- 将拷贝构造私有化,这个时候就不能通过拷贝构造创建对象
- 将唯一的对象指针私有化
- 提供一个获取唯一对象的接口
```c++
class Singleton
{
public:
    // 5. 提供一个获取唯一对象的接口
	static Singleton* GetInstance() {
        if (m_instance == nullptr) {
            m_instance = new Singleton();
        }
		return m_instance;
	}
    ~Singleton() {
        std::cout<<"Singleton Destructor "<<std::endl;
    }

private:
	// 1. 将默认的构造函数私有化,这样就不能创建出对象
	Singleton() {
        std::cout << "Singleton Constructor" << std::endl;
    }

	// 3.将拷贝构造函数私有化，这个时候就不能通过拷贝构造创建对象
	Singleton(const Singleton& s)=delete; // 禁止拷贝
	Singleton& operator=(const Singleton s)=delete; // 禁止赋值

    // 4. 将唯一的对象指针私有化
	static Singleton *m_instance; // static 类内声明,内外定义 = nullptr
};

// 2. 在类中创建出唯一的对象,new出一个对象，并且将对象设置为static
Singleton* Singleton::m_instance = nullptr;

int main() 
{
    Singleton* obj = Singleton::GetInstance();
    Singleton* obj_bak = Singleton::GetInstance();
    return 0;
}
```
运行结果:
```shell
Singleton Constructor
```
可以看到,获取了两次类的实例,却只有一次类的构造函数被调用,表明只生成了唯一实例,这个是最基础版本的单例实现.当然还存在一些问题:    

- 这个代码只适合在单线程下,当多线程时,是不安全的。当多线程获取单例时有可能引发竞态条件：第一个线程在`if`中判断 `m_instance`是空的,于是开始实例化单例;同时第二个线程也尝试获取单例,这个时候判断`m_instance`还是空的,于是也开始实例化单例;这样就会实例化出两个对象,这将违反了单例的准则,这也是线程安全问题的由来;  

- 内存泄漏: 注意到类中只负责`new`出对象,却没有负责`delete`对象,因此只有构造函数被调用,析构函数却没有被调用,因此会导致内存泄漏。  

### 懒汉模式与饿汉模式
单例分为两种实现方法：
- 懒汉模式
    - 第一次用到类实例的时候才会去实例化.只有程序想要使用这个对象的时候才去创建出来  
```c++
class Singleton
{
public:
    static Singleton* GetInstance(){
        if(m_instance == nullptr) {
            m_instance = new Singleton;
        }      
        return m_instance;
    }

private:
    static Singleton *m_instance;
};

Singleton* Singleton::m_instance = nullptr;
```    
- 饿汉模式  
    - 单例类定义的时候就进行了实例化,不管程序有没有用到这个对象,都要构造处理,问题比较少
```c++
class Singleton
{
public:
    static Singleton* GetInstance(){    
        return m_instance;
    }

private:
    static Singleton *m_instance;
};
// 单例类定义的时候就进行了实例化
Singleton* Singleton::m_instance = new Singleton;
```
 
 ### 多线程加锁
 在使用多线程的时候由于获取单例时有可能引发竞态条件,因此可以进行加锁来解决。  
 ```c++
class Singleton
{
public:
    static Singleton* GetInstance() {
        m_lock.lock();
        if(m_instance == nullptr) {
            m_instance = new Singleton;
        }      
        m_lock.unlock();    
        return m_instance;
    }   

private:
    static Singleton *m_instance;
    static mutex m_lock;
};
Singleton* Singleton::m_instance = nullptr;
 ```
 这种写法不会出现上面两个线程都执行到`m_instance == nullptr`里面的情况,当线程A在执行`m_instance = new Singleton`的时候,线程B如果调用了`GetInstance`,一定会被阻塞在加锁处,等待线程A执行结束后释放这个锁。从而是线程安全的。但是这种写法性能非常低下,因为每次调用`GetInstance()`都会加锁释放锁，而这个步骤只有在第一次`new Singleton`才是有必要的，只要`m_instance`被创建出来了,不管多少线程同时访问，使用`if (m_instance == nullptr)` 进行判断都是足够的(只是读操作,不需要加锁),没有线程安全问题，加了锁之后反而存在性能问题。 因此引出`DCLP`(双重检查锁模式)


### 双重检查锁模式
上面写法是不管任何情况都会去加锁,然后释放锁,而对于读操作是不存在线程安全的(出现脏读),故只需要在第一次实例创建的时候加锁,以后不需要。下面先看一下DCLP的实现:
```c++
class Singleton
{
public:
    static Singleton* GetInstance()const {
        if(m_instance == nullptr) { // 第一次检查
            m_lock.lock();
            if(m_instance == nullptr) { // 第二次检查
                m_instance = new Singleton;
            }
            m_lock.unlock();
        }
        return m_instance;
    }   

private:
    static Singleton *m_instance;
    static mutex m_lock;
};
Singleton* Singleton::m_instance = nullptr;
```
`DCLP`的关键在于,大多数对`GetInstance`的调用会看到`m_instance`是非空的,因此甚至不用尝试去初始化它。因此，`DCLP`在尝试获取锁之前检查`m_instance`是否为空。只有当检查成功（也就是`m_instance`还没有被初始化）时才会去获得锁，然后再次检查`m_instance`是否仍然为空（因此命名为双重检查锁）。**第二次检查是必要，因为就像我们刚刚看到的,很有可能另一个线程偶然在第一次检查之后,获得锁成功之前初始化m_instance。**


### 自动回收
关于释放的问题, 可以使用一个Garbo类,清理工人
```c++
class Singleton {
private:
    Singleton() {}

    static Singleton *m_instance;
    static mutex m_lock;
public:
    Singleton* GetInstance() {
        if (m_instance == nullptr) {
        lock_guard<mutex> guard(m_lock);
        if (m_instance == nullptr)
            m_instance = new Singleton();
        }
        return m_instance;
    }

    // 实现一个内嵌垃圾回收类
    class Garbo
    {
    public:
        ~Garbo() {
            if(Singleton::m_instance)
                delete Singleton::m_instance;
        }
    };
    static Garbo m_Garbo; // 定义一个静态成员变量,程序结束时,系统会自动调用它的析构函数从而释放单例对象
};

Singleton *Singleton::m_instance = nullptr;
Singleton::Garbo m_Garbo; 
```
看起来上述代码非常美好,可是过了相当一段时间后,才发现这个漏洞,原因是：**内存读写的乱序执行(编译器问题)。**    

再次考虑初始化`m_instance`的那一行：    
```c++
m_instance = new Singleton();
```

这条语句会导致三个事情的发生：   
- 分配能够存储Singleton对象的内存；      
- 在被分配的内存中构造一个singleton对象；     
- 让`m_stance`指向这块被分配的内存。     

可能会认为这三个步骤是按顺序执行的,但实际上只能确定步骤1是最先执行的,步骤2,3却不一定。问题就出现在这。

线程A调用`GetInstance`，执行第一次`m_instance`的测试,获得锁,按照1,3,执行，然后被挂起。此时`m_instance`是非空的，但是`m_instance`指向的内存中还没有`Singleton`对象被构造。   
线程B调用`GetInstance`,判定`m_instance`非空, 将其返回给`GetInstance`的调用者。调用者对指针解引用以获得`Singleton`,一个还没有被构造出的对象.`bug`就出现了。    


### 最推荐的懒汉式单例
这种方法又叫做`Meyers' SingletonMeyer's`的单例,局部静态变量
```c++
#include <iostream>

class Singleton
{
public:
    ~Singleton() {
        std::cout<<"Singleton Destructor"<<std::endl;
    }

    Singleton(const Singleton&)=delete; // 禁止拷贝

    Singleton& operator=(const Singleton&)=delete; // 禁止赋值

    static Singleton& GetInstance() {
        static Singleton m_instance;
        return m_instance;

    }
private:
    Singleton(){
        std::cout<<"Singleton Constructor "<<std::endl;
    }
};

int main(int argc, char *argv[])
{
    Singleton& obj = Singleton::GetInstance();
    Singleton& obj_bak = Singleton::GetInstance();
    return 0;
}
```
这样保证了并发线程在获取静态局部变量的时候一定是初始化过的,所以具有线程安全性。


**[⬆ 返回顶部](#目录)**
