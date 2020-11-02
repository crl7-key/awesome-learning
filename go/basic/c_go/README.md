# Cgo
* [go语言中使用C语言](#go语言中使用C语言)
* [C语言中使用go语言](#C语言中使用go语言)

# go语言中使用C语言

`go`代码中使用C代码,在`go`语言的函数块中,以注释的方式写入`C`代码,然后紧跟`import “C”` 即可在`go`代码中使用`C`函数

```go
package main

/*
#include <stdio.h>
#include <stdlib.h>
void c_print(char *str) {
    printf("%s\n", str);
}
*/
import "C" //import “C” 必须单起一行，并且紧跟在注释行之后
import "unsafe"

func main() {
	s := "hello world"
	cs := C.CString(s)               // 字符串映射
	C.c_print(cs)                    // 调用C函数
	defer C.free(unsafe.Pointer(cs)) // 释放内存
}
```

- `go`代码中的`C`代码,需要用注释包裹,块注释和行注释均可，其次`import “C”`是必须的,并且和上面的`C`代码之间不能用空行分割,必须紧密相连

- 如果执行go run **时出现 
> command-line-arguments could not determine kind of name for  xxx

- 那么就需要考虑是不是`improt “C”`和上面的`C`代码有没有紧挨着导致了

- `import “C”`并没有导入一个名为`C`的包,这里的`import “C”`类似于告诉`Cgo`将之前注释块中的`C`代码生成一段具有包装性质的`Go`代码

- 访问`C`语言中的函数需要在前面加上`C.`前缀,如`C.Cstring C.go_print C.free`

- 对于`C`语中的原生类型,`Cgo`都有对应的`Go`语言中的类型,如`go`代码中`C.int`,`C.char`对应于`c`语言中的`int`,`signed char`,而`C`语言中`void*`指针在`Go`语言中用特殊的`unsafe.Pointer(cs)`来对应,而`Go`语言中的`string`类型,在`C`语言中用字符数组来表示,二者的转换需要通过`go`提供的一系列函数来完成:
 - `C.Cstring` : 转换`go`的字符串为`C`字符串,`C`中的字符串是使用`malloc`分配的,所以需要调用`C.free`来释放内存
 - `C.Gostring`: 转换`C`字符串为`go`字符串
 - `C.GoStringN`:  转换一定长度的`C`字符串为`go`字符串
- 需要注意的是每次转换都会导致一次内存复制,所以字符串的内容是不可以修改的
- 可以利用`defer C.free`和`unsafe.Pointer`显示释放调用`C.Cstring`所生成的内存块

执行:
> $ go run testC.go


# C语言中使用go语言
可以从`C`应用程序执行`Go`函数。应使用以下注释行将其导出：
```go
//export <your_function_name>
```
例如:
```go
package main

import "C"
import "fmt"

//export SayHello
func SayHello(name string) {
    fmt.Printf("Nautilus says: Hello, %s!\n", name)
}

//export SayBye
func SayBye() {
	fmt.Println("Nautilus says: Bye!")
}

func main() { // main函数是必须的 有main函数才能让cgo编译器去把包编译成C的库
}
```
- `go`代码中的`main`函数是必须的,有`main`函数才能让`cgo`编译器去把包编译成`c`的库
- `import “C”`是必须的,如果没有`import “C”`将只会`build`出一个`.a`或者`.so`文件,而缺少`.h`文件
- `//exoort SayHello`这里的`go_print`要和下面的的`go`函数名一致,并且下面一行即为要导出的`go`函数
- 通过`go build`的编译选项,将`go`代码编译成共享库以供`c`代码调用,命令执行完毕后会生成两个文件`libname.a`和`libname.h`,`libname.h`中定义了`go`语言中的类型在`C`中对应的类型和导出的`go`函数的函数声明
    - 生成动态库 ：`go build -v -x -buildmode=c-shared -o libprint.so print.go。`
    - 生成静态库 ：`go build -v -x -buildmode=c-shared -o libprint.a print.go。`
    - 或者使用`go build -buildmode=c-archive -o libprint.a print.go`

编译成功后，只需在`c`代码中引入新生成的头文件及编译时链接动态库即可实现`go`函数的调用。代码如下：
```c
// filename: c_go.c
#include "libprint.h" // 引入go代码导出的生成的C头文件

#include <stdio.h>

int main() {
  printf("This is a C Application.\n");
  GoString name = {"Jack", 4};      // go中的字符串类型在c中为GoString
  SayHello(name);
  SayBye();
  return 0;
}
```
通过`gcc -o test c_go.c -L. libname.so`,即可编译成可执行程序。注意,运行前必须确定共享库运行时查找路径中存在需要链接的共享库，可通过将`so`库路径放到`/usr/lib`或者修改环境变量`LD_LIBRARY_PATH`。

例如:
> gcc -o test c_go.c -L. libprint.a  
可以在当前目录下看到生成了一个名为`test`的可执行文件,运行文件:  
> ./test

