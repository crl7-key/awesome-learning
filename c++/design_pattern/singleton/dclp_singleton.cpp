#include <iostream>
#include <mutex>

using namespace std;

class Singleton
{
public:
    static Singleton* GetInstance() {
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

int main(int argc, char const *argv[])
{
    Singleton* obj = Singleton::GetInstance();
    Singleton* obj_bak = Singleton::GetInstance();
    return 0;
}
