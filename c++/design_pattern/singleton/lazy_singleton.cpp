#include <iostream>

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

int main(int argc, char const *argv[])
{
    Singleton* obj = Singleton::GetInstance();
    Singleton* obj_bak = Singleton::GetInstance();
    return 0;
}
