# auto
让编译器在编译器就推导出变量的类型,可以通过`=`右边的类型推导出变量的类型
```c++
auto i = 10; // 10是int型,可以自动推导出i是int
```

## auto使用时需要注意:
- `auto`变量必须在定义时进行初始化操作(如果不进行初始化操作,那么`auto`关键字就不能进行变量类型的推导)
- 定义一个`auto`序列的变量时,必须是同一种类型，如：
```c++
auto a = 1, b = 2, c = 3; // ok
// auto a = 1, b = 2.0, c = 'c';  // error
```
- 如果表达式是引用,则去除引用语义
```c++
int32_t a = 1;
int32_t& b = a;
auto c = b; // 此时c的类型被推导为 int32_t，而不是int32_t&
auto& c = b; // 此时c的类型才是int32_t&
```

- 如果表达式是`const`或`volatile`（或两者都有）,则去除const/volatile语义
```c++
const int a = 10;
auto &b = a;// 因为auto带上&，故不去除const，b类型为const int
b = 10; //非法
```
这是因为如何去掉了`const`，则`b`为`a`的`非const引用`,通过`b`可以改变`a`的值,则显然是不合理的。
- 初始化表达式为数组时,`auto`关键字推导类型为指针。
```c++
int a[3] = { 1, 2, 3 };
auto b = a;
std::cout << typeid(b).name() << std::endl;  // output : int*
```

- 若表达式为数组且`auto`带上`&`,则推导类型为数组类型。
```c++
int a[3] = { 1, 2, 3 };
auto & b = a;
std::cout << typeid(b).name() << std::endl; // output::
```

- 函数或者模板参数不能被声明为`auto`
```c++
void func(auto a)  {// error
//... 
}
```

- `auto`不是一个真正的类型,仅仅是一个占位符,不能使用一些以类型为操作数的操作符,如`sizeof`或`typeid`
```c++
std::cout << sizeof(auto) std::endl; // error

std::cout << typeid(auto).name() std::endl; // error
```