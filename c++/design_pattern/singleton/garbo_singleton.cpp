#include <iostream>
#include <mutex>

using namespace std;
class Singleton {
private:
    Singleton() {}

    static Singleton *m_instance;
    static mutex m_lock;
public:
    Singleton *GetInstance() {
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


int main(int argc, char const *argv[])
{
    Singleton* obj;
    obj->GetInstance();
    
    return 0;
}


