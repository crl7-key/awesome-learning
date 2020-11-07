# Go 的错误机制
- 没有异常机制
- `error`类型实现来`error`接口
- 可以通过`errors.New`来快速创建错误实例
```go
type error interface {
    Error() string
}

errors.New("n must be in the range [0,10]")
```

# panic
- `panic`用于不可以恢复的错误
- `panic`退出前会执行`defer`指定的内容


# panic Vs os.Exit
- `os.Exit`退出时不会调用`defer`指定的函数
- `os.Exit`退出时不输出当前调用栈信息

# recover
java异常
```java
    try{
        ...
    }catch(Throwable t) {

    }
```
c++异常
```c++
    try {
        ...
    }catch(...) {

    }
```

go:
```go
defer func() {
    if err := recover(); err != nil {
        // 恢复错误
    }
}
```

最常见的“错误恢复”
```go
defer func() {
    if err := recover(); err != nil {
        log.Error("recovered panic ",err)
    }
}()
```
以上代码使用时需要当心
- 形成僵尸服务进程,导致`health check`失效
- `“Let it Crash!" `往往是我们恢复不确定性错误的最好方法。
