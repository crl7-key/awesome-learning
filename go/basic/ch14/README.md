# Thread vs Groutine
- 创建时默认的`stack`的大小
  - `JDK5`以后`java Thread stack`默认为`1M`
  - `Groutine`的`Stack`初始化为`2k`
- 和`KSE`(Kernel Space Entity)的对应关系
  - `Java Thread`是`1:1`
  - `Groutine`是`M:N`

# Lock
```
Lock lock = ...;
lock.lock();
try {
  // process(thread-safe)
}catch(Exception ex) {

}finally {
  lock.unlock();
}
``` 

# WaitGroup
```go
var wg sync.WaitGroup
for i := 0; i < 5000; i ++ {
  wg.Add(1)
  go func() {
    defer func() {
      wg.Done()
    }()
    ....
  }()
}
  wg.Wait()
```