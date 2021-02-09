# Go语言实践之error


`golang`搜索推荐使用网站：[https://pkg.go.dev]()

`golang`必读：[Effective Go](https://golang.org/doc/effective_go.html)

`golang`源码路径：`/your-install-path/sdk/go-version/src`
## 目录
* [Error vs Exception](#Error-vs-Exception)
* [Error Type](#Error-Type)
* [Handling Error](#Handling-Error)
* [Go 1.13 errors](#Go-1.13-errors)
* [Go 2 Error inspection](#Go-2-Error-inspection)

## Error
在`Go`中`error`就是普通的一个接口，普通的值.  
[error definition](http://golang.org/pkg/builtin/#error)

```go
type error interface {
    Error() string
}
```
我们经常使用`errors.New()`来返回一个`error`对象。   
[errorString definition](http://golang.org/src/pkg/errors/errors.go)
```go
type errorString struct {
    s string
}
```
[errorString Method](https://golang.org/src/pkg/errors/errors.go)
```go
func (e *errorString) Error() string {
	return e.s
}
```

基础库中大量自定义的`error`。   
[basic error](http://golang.org/src/pkg/bufio/bufio.go)
```go
// 哨兵 error
var (
	ErrInvalidUnreadByte = errors.New("bufio: invalid use of UnreadByte")
	ErrInvalidUnreadRune = errors.New("bufio: invalid use of UnreadRune")
	ErrBufferFull        = errors.New("bufio: buffer full")
	ErrNegativeCount     = errors.New("bufio: negative count")
)
```
`errors.New()`返回的是内部`errorString`对象的指针。   
[errors.New](http://golang.org/src/pkg/errors/errors.go)
```go
// New returns an error that formats as the given text.
// Each call to New returns a distinct error value even if the text is identical.
func New(text string) error {
	return &errorString{text}
}
```

## Error vs Exception
各个语言的演进历史：
- `C`
    单返回值，一般通过传递指针作为入参，返回值为`int`表示成功还是失败。
    ```c
    int func() {
        int err = -1;
        ...
        return err;
    }
    ```

- `C++`
    引入了`exception`,但是无法知道被调用方会抛出什么异常。

- `Java`
    引入了`checked exception`,方法的所有者必须声明，调用者必须处理。在启动时抛出大量的异常是司空见惯的事情，并且它们的调用堆栈中尽责地记录下来。`Java`异常不再是异常，而是变得司空见惯了。它们从良性到灾难性都有使用，异常的严重性由函数的调用者来区分。

`golang`的处理异常逻辑是不引入`exception`,支持多参数返回，所以很容易的在函数签名中带上实现了`error interface`的对象，交由调用者来判定。   
```go
package main

import "fmt"

func handle()(int,error) {
    return 1,nil
}

func main() {
    i,err := handle()
    if err != nil {
        return
    }
    fmt.Println(i)
}
```
**如果一个函数返回了`value`,`error`,不能对这个`value`做任何假设，必须先判定`error`。唯一可以忽略`error`的是，如果连`value`也不关心。**

`golang`中有`panic`的机制，如果认为和其他语言的`exception`一样，那就错了。当我们抛出异常的时候，相当于把`exception`扔给了调用者来处理。

**比如，在`C++`中，把`string`转为`int`，如果转换失败，会抛出异常。或者在`java`中转换`string`为`data`失败时，会抛出异常。**

**在`Golang`中 `panic`意味这`fatal error`(即程序挂了)，不能假设调用者来解决`panic`,意味者代码不能继续运行下去。**

总结：   
**使用多个返回值和一个简单的约定，`Go`解决了让程序员知道什么时候出了问题，并为真正的异常情况保留了`panic`。**


对于真正意味的情况，那些表示不可恢复的程序错误，例如索引越界、不可恢复的环境问题、栈溢出，才使用`panic`。对于其他的错误情况，应该是期望使用`error`来进行判定。



## Error type
### Sentinel Error
预定义的特定错误，称之为`sentinel error`,这个名字来源于计算机编程中使用一个特定值来表示不可能进行进一步处理器的做法。所以对于`golang`来说，需要使用特定的值表示错误。例如：
```go
    if err == ErrSomething{...}
```
类似的[io.EoF](https://golang.org/pkg/io/#pkg-variables),更底层的[syscall.ENOENT](https://golang.org/pkg/syscall/)。
**使用`sentinel`值是最不灵活的错误处理策略，因为调用方必须使用`==`将结果于预先声明的值进行比较。当您想要提供更多的上下文时，这就出现了一个问题，因为返回一个不同的错误将破坏相等性检查。**

**甚至是一些有意义的`fmt.Errorf`携带一些上下文，也会破坏调用者的`==`,调用者将被迫查看`error.Error()`方法输出，以查看它是否与特定的字符串匹配。**

- 不依赖检查`error.Error`的输出。  
**不应该依赖检测`error.Error`的输出，`Error`方法存在于`error`接口主要用于方便程序员使用，但不是程序(编写测试可能会依赖这个返回)。这个输出的字符串用于记录日志、输出到`stdout`等。**

- `Sentinel errors`成为`API`公共部分

  如果您的公共函数或方法返回一个特定值的错误，那么该值必须是公共的，当然要有文档记录，这会增加`API`的表面积。
 
  如果`API`定义了一个返回特定错误的`interface`，则该接口的所有实现都将限制为仅返回该错误，即使它们可以提供更具描述性的错误。

  比如[io.Reader](https://golang.org/pkg/io/#Reader)。像[io.Copy](https://golang.org/pkg/io/#Copy)这类函数需要`read`的实现者，比如`io.EOF`来告诉我们调用这没有更多数据来，但这又不是错误。


- `Sentinel errors`在两个包之间创建了依赖。
    `sentinel errors`最糟糕的问题是它们在两个包之间创建了源代码依赖关系。例如，检查错误是否等于`io.EOF`,您的代码必须导入`io`包。这个特定的例子听起来并不那么糟糕，因为它非常常见，但是想象一下，当项目中的许多包导出错误值时，存在耦合，项目中的其他包必须导入这些错误值才能检查特定的错误条件(`in the form of an import loop`)。

- 结论： 尽可能避免`sentinel errors`
    建议是避免在编写的代码中使用`sentinel errors`。在标准库中有一些使用它们的情况，但这不是一个初学者应该模仿的模式。


### Error types
`Error type`是实现了`error`接口的自定义类型。例如`MyError`类型记录了文件和行号以展示发生了什么。
```go
type MyError struct {
	Msg  string
	File string
	Line int
}

func (e *MyError) Error() string {
	return fmt.Sprintf("%s:%d: %s", e.File, e.Line, e.Msg)
}

func test() error {
	return &MyError{"Something happend", "server.go", 42}
}
```
因为`MyError`是一个`type`，调用者可以使用断言转换成这个类型，来获取更多的上下文信息。
```go
func main() {
    err := test()
    switch err := err.(type) {
    case nil:
		// call sucdeeded, nothing to do
	case *MyError:
		fmt.Println("error occurred on line: ", err.Line)
	default:
		// unknown error
    }
}
```
输出：
```sh
error occurred on line:  42
```
与错误值相比，错误类型的一大改进使它们能够包装底层错误以提供更多上下文。一个不错的例子就是[os.PathError](https://golang.org/pkg/os/#PathError),它提供了底层执行了什么操作、哪个路径出了什么问题。
```go
type PathError struct {
    Op   string
    Path string
    Err  error
}

func (e *PathError) Error() string
```
调用者要使用类型断言和类型`switch`，就要让自定义的`error`变为`public`。这种模型会导致和调用者产生强耦合，从而导致`API`变得脆弱。


结论：  

尽量避免使用`error types`,虽然错误类型比`sentinel errors`更好，因为它们可以捕获关于出错的更多上下文，但是`error types`共享`error values`许多相同的问题。建议是避免错误类型，或者至少避免将它们作为公共`API`的一部分。

### Opaque errors

不透明错误处理，即只需返回错误而不假设其内容。因为虽然您知道发生了错误，但您没有能力看到错误的内部。作为调用者，关于操作的结果，您所知道的就是它起作用了，或者没有起作用(成功或者失败)。这是最灵活的错误处理策略，因为它要求代码和调用者之间的耦合最少。
```go
func fn() error {
    x,err := xxx.Foo()
    if err != nil {
    return err
    }
    // use x
}
```

## Handling Error
- `Indented flow is for errors`
无错误的正常流程代码，将成为一条直线，而不是缩进的代码。
```go
f,err := os.Open(path)
if err != nil {
    // handle error
}
// do stuff


f,err := os.Open(path)
if err == nil {
    // do stuff
}
// handle error
```
上述代码中比较好的方式是第一个版本。

- `Eliminate error handling by eliminating errors`
例如：
```go
func AuthenticateRequest(r *Request) error {
    err := authenticate(r.User)
    if err != nil {
        return nil
    }
    return nil
}
```
上述代码可以更简洁：
```go
 func AuthenticateRequest(r *Request) error {
    return authenticate(r.User)
}
```


**[⬆ 返回顶部](#Problems)**



