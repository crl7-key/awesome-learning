#include <iostream>

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