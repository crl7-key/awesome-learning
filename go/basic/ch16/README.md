# select

`select`语句类似于`switch`语句，但是`select`会随机执行一个可运行的`case`。如果没有`case`可运行，它将阻塞，直到有`case`可运行。

`select`是`Go`中的一个控制结构，类似于用于通信的`switch`语句。每个`case`必须是一个通信操作，要么是发送要么是接收。 `select`随机执行一个可运行的`case`。如果没有`case`可运行，它将阻塞，直到有`case`可运行。一个默认的子句应该总是可运行的

`Go`编程语言中`select`语句的语法如下：
```go
select {
    case communication clause  :
       statement(s);      
    case communication clause  :
       statement(s);
    /* 你可以定义任意数量的 case */
    default : /* 可选 */
       statement(s);
}
```
- 每个`case`都必须是一个通信
- 所有`channel`表达式都会被求值
- 所有被发送的表达式都会被求值
- 如果任意某个通信可以进行，它就执行；其他被忽略。
- 如果有多个`case`都可以运行，`select`会随机公平地选出一个执行。其他不会执行。否则：
    - 如果有`default`子句，则执行该语句。
    - 如果没有`default`字句，`select`将阻塞，直到某个通信可以运行；`Go`不会重新对`channel`或值进行求值。


`select`可以监听`channel`的数据流动

`select`的用法与`switch`语法非常类似，由`select`开始的一个新的选择块，每个选择条件由`case`语句来描述

与`switch`语句可以选择任何使用相等比较的条件相比，`select`由比较多的限制，其中最大的一条限制就是每个`case`语句里必须是一个`IO`操作
```go
select { //不停的在这里检测
    case <-chanl : //检测有没有数据可以读
    //如果chanl成功读取到数据，则进行该case处理语句
    case chan2 <- 1 : //检测有没有可以写
    //如果成功向chan2写入数据，则进行该case处理语句

    //假如没有default，那么在以上两个条件都不成立的情况下，就会在此阻塞//一般default会不写在里面，select中的default子句总是可运行的，因为会很消耗CPU资源
    default:
    //如果以上都没有符合条件，那么则进行default处理流程
}
```
**多渠道的选择**
```go
select {
case ret := <- retCh1:
    fmt.Printf("result %s",ret)
case ret := <-retCh2:
    fmt.Printf("result %s",ret)
default:
    fmt.Printf("No one returned")
}
```

**超时控制**
```go
select {
case ret := <-retCh:
    fmt.Printf("result %s",ret)
case <-time.After(time.Second * 1):
    fmt.Println("time out")
}
```

**判断channel是否阻塞**
```go
//在某些情况下是存在不希望channel缓存满了的需求的，可以用如下方法判断
ch := make (chan int, 5)
//...
data := 0
select {
case ch <- data:
default:
    //做相应操作，比如丢弃data。视需求而定
}
```

**退出**
```go
//主线程（协程）中如下：
var shouldQuit=make(chan struct{})
fun main(){
    {
        //loop
    }
    //...out of the loop
    select {
        case <-c.shouldQuit:
            cleanUp()
            return
        default:
        }
    //...
}

//再另外一个协程中，如果运行遇到非法操作或不可处理的错误，就向shouldQuit发送数据通知程序停止运行
close(shouldQuit)
```