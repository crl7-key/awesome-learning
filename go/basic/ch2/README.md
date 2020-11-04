# 编写测试程序
- 源码文件以`_test`结尾:`xxx_test.go`
- 测试方法名以`Test`开头: `func TestXXX(t *testing.T) {...}`
```go
package try_test

import "testing"

func TestFirstTry(t *testing.T) {
	t.Log("My first try!")
}
```

# 变量赋值
与其它主要编程语言的差异
- 赋值可以进行自动类型推断
```go
a := 1
b := 1
```
- 在一个赋值语句中可以对多个变量进行同时赋值

# 常量定义
与其它主要编程语言的差异
- 快速设置连续值
```go
const (
	Monday = iota + 1
	Tuesday
	Wednesday
	Thursday
	Friday
	Saturday
	Sunday
)

const (
	Open = 1 << iota
	Close
	Pending
)
```

## 实现Fibonacci数列
