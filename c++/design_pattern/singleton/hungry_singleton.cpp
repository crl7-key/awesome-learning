#include <iostream>

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

int main(int argc, char const *argv[])
{
    Singleton* obj = Singleton::GetInstance();
    Singleton* obj_bak = Singleton::GetInstance();
    return 0;
}
