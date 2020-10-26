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