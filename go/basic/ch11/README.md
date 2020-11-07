# Go 接口

接口（`interface`）定义了一个对象的行为规范，只定义规范不实现，由具体的对象来实现规范的细节。

在Go语言中接口（`interface`）是一种类型，一种抽象的类型。

`interface`是一组`method`的集合，是`duck-type programming`的一种体现。接口做的事情就像是定义一个协议（规则），只要一台机器有洗衣服和甩干的功能，我就称它为洗衣机。**不关心属性（数据），只关心行为（方法）。**
## 为什么要使用接口?
```go
type Cat struct{}

func (c Cat) Say() string { return "喵喵喵" }

type Dog struct{}

func (d Dog) Say() string { return "汪汪汪" }

func TestAnimal(t *testing.T) {
	c := Cat{}
	fmt.Println("猫:", c.Say())
	d := Dog{}
	fmt.Println("狗:", d.Say())
}
```
上面的代码中定义了猫和狗，然后它们都会叫，在主要的函数中明显有重复的代码，如果我们后续再加上猪、青蛙等动物的话，我们的代码还会一直重复下去。那我们能不能把它们当成“能叫的动物”来处理呢？
`Go`语言中为了解决类似上面的问题，就设计了接口这个概念。接口区别于我们之前所有的具体类型，接口是一种抽象的类型。当你看到一个接口类型的值时，你不知道它是什么，唯一知道的是通过它的方法能做什么。

## 接口的定义
- 接口是一个或多个方法签名的集合。
- 任何类型的方法集中只要拥有该接口'对应的全部方法'签名。就表示它 "实现" 了该接口，无须在该类型上显式声明实现了哪个接口。这称为·Structural Typing·。
- 所谓对应方法，是指有相同名称、参数列表 (不包括参数名) 以及返回值。当然，该类型还可以有其他方法。

- 接口只有方法声明，没有实现，没有数据字段。
- 接口可以匿名嵌入其他接口，或嵌入到结构中。
- 对象赋值给接口时，会发生拷贝，而接口内部存储的是指向这个复制品的指针，既无法修改复制品的状态，也无法获取指针。
- 只有当接口存储的类型和对象都为`nil`时，接口才等于`nil`。
- 接口调用不会做`receiver`的自动转换。
- 接口同样支持匿名字段方法。
- 接口也可实现类似OOP中的多态。
- 空接口可以作为任何类型数据的容器。
- 一个类型可实现多个接口。
- 接口命名习惯以`er`结尾。

每个接口由数个方法组成，接口的定义格式如下：
```go
type 接口类型名 interface{
        方法名1( 参数列表1 ) 返回值列表1
        方法名2( 参数列表2 ) 返回值列表2
        …
}
```
其中：
- 接口名：使用`type`将接口定义为自定义的类型名。`Go`语言的接口在命名时，一般会在单词后面添加`er`，如有写操作的接口叫`Write`r，有字符串功能的接口叫`Stringer`等。接口名最好要能突出该接口的类型含义。
- 方法名：当方法名首字母是大写且这个接口类型名首字母也是大写时，这个方法可以被接口所在的包（`package`）之外的代码访问。  
- 参数列表、返回值列表：参数列表和返回值列表中的参数变量名可以省略。   
例如：
```go
type Programmer interface {
	WriteHelloWorld() string
}
```
当你看到这个接口类型的值时，你不知道它是什么，唯一知道的就是可以通过它的`WriteHelloWorld`方法来做一些事情。

## 实现接口的条件
一个对象只要全部实现了接口中的方法，那么就实现了这个接口。换句话说，**接口就是一个需要实现的方法列表。**
例如：定义一个`Sayer`接口
```go
// Sayer接口
type Sayer interface {
	Say() string
}
```
定义`dog`和`cat`两个结构体：
```go
type Cat struct{}
type Dog struct{}
```
因为`Sayer`接口里只有一个`Say`方法，所以我们只需要给`dog`和`cat`分别实现`Say`方法就可以实现`Sayer`接口了。
```go
// dog实现了Sayer接口
func (d Dog) Say() string{
    return "汪汪汪"
}

// cat实现了Sayer接口
func (c cat) Say() string {
    return "喵喵喵"
}
```
接口的实现就是这么简单，只要实现了接口中的所有方法，就实现了这个接口。


## 与其它主要编程语言的差异
- 接口为非入侵性,实现不依赖于接口定义
- 所以接口的定义可以包含在接口使用者包内


关于接口需要注意的是，只有当有两个或两个以上的具体类型必须以相同的方式进行处理时才需要定义接口。不要为了接口而写接口，那样只会增加不必要的抽象，导致不必要的运行时损耗。


# 自定义类型
```go
type IntConvertionFn func(n int)int
type Mypoint int
```

# go 继承
代码实现[extension](extension_test/extension_test.go)

# go 多态
代码实现[polymorphism](polymorphism_test/polymorphism_test.go)

# 空接口与断言
- 空接口可以表示任何类型
- 通过断言来将空接口转换为制定类型
```go
v,ok := p.(int) // ok = true时为转换成功
```

# Go接口最佳实践
- 倾向于使用小的接口定义,很多接口只包含一个方法
```go
type Reader interface {
    Read(p []byte)(n int,err error)
}

type Writer interface {
    Write(p []byte)(n int,err error)
}
```
- 较大的接口定义,可以由多个小接口定义组合而成
```go
type ReadWriter interface {
    Reader
    Writer
}
```
- 只依赖于必要功能的最小接口
```go
func StoreData(reader Reader) {
    ....
}
```