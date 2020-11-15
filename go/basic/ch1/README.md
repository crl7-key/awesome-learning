# Hello_world

## 环境变量
```
GOROOT      指向GOLANG的安装目录
GOPATH      指向GO第三方库所在路径,可以和GOROOT是同一个路径,在使用go get和 go install时会被引用
```

```go
package main // 包,表明代码所在的模块(包)

import "fmt" // 引入代码依赖

// 功能实现
func main() {
	fmt.Println("Hello world")
}

```

## 应用程序入口
- 必须是`main`包: `package main`
- 必须是main方法: `func main`
- 文件名不一定是`main.go`


## 与其他主要编程语言的差异
- 退出返回值
    - Go中main函数不支持任何返回值
    - 通过os.Exit来返回状态

```go
package main // 包,表明代码所在的模块(包)

import (
    "fmt" // 引入代码依赖
    "os"
)
// 功能实现
func main() {
    fmt.Println("Hello world")
    os.Exit(0)
}
```

- 获取命令行参数
  - main函数不支持传入参数
```go
func main(arg []string) // error
```
  - 在程序中直接通过`os.Args`获取命令行参数
```go
package main // 包,表明代码所在的模块(包)

import (
	"fmt"
	"os"
) // 引入代码依赖

// 功能实现
func main() {
	if len(os.Args) > 1 {
		fmt.Println("Hello World", os.Args[1])
	}
	os.Exit(0)
} 
```