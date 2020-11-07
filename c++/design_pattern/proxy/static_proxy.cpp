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
