# 函数

* [函数定义](#函数定义)
* [函数声明](#函数声明)
* [函数参数](#函数参数)
* [函数返回值](#函数返回值)
* [匿名函数](#匿名函数)
* [闭包](#闭包)    
* [与其它主要编程语言的差异](#与其它主要编程语言的差异)
* [defer函数](#defer函数)
* [异常处理](#异常处理)


## 函数定义
- 无需声明原型。
- 支持不定变参。
- 支持多返回值。
- 支持命名返回参数。 
- 支持匿名函数和闭包。
- 函数也是一种类型，一个函数可以赋值给变量。

- 不支持 嵌套 (`nested`) 一个包不能有两个名字一样的函数。
- 不支持 重载 (`overload`) 
- 不支持 默认参数 (`default parameter`)。

## 函数声明：
函数声明包含一个函数名,参数列表, 返回值列表和函数体。如果函数没有返回值，则返回列表可以省略。函数从第一条语句开始执行，直到执行`return`语句或者执行函数的最后一条语句。

函数可以没有参数或接受多个参数。

注意类型在变量名之后 。

当两个或多个连续的函数命名参数是同一类型，则除了最后一个类型之外，其他都可以省略。

函数可以返回任意数量的返回值。

使用关键字`func`定义函数，左大括号依旧不能另起一行。
```go
func test(x, y int, s string) (int, string) {
    // 类型相同的相邻参数，参数类型可合并。 多返回值必须用括号。
    n := x + y          
    return n, fmt.Sprintf(s, n)
}
```
函数是第一类对象，可作为参数传递。建议将复杂签名定义为函数类型，以便于阅读。
```go
package main

import "fmt"

func test(fn func() int) int {
    return fn()
}
// 定义函数类型。
type FormatFunc func(s string, x, y int) string 

func format(fn FormatFunc, s string, x, y int) string {
    return fn(s, x, y)
}

func main() {
    s1 := test(func() int { return 100 }) // 直接将匿名函数当参数。

    s2 := format(func(s string, x, y int) string {
        return fmt.Sprintf(s, x, y)
    }, "%d, %d", 10, 20)

    println(s1, s2)
}
```

## 函数参数
函数定义时指出，函数定义时有参数，该变量可称为函数的形参。形参就像定义在函数体内的局部变量。

但当调用函数，传递过来的变量就是函数的实参，函数可以通过两种方式来传递参数：

值传递：指在调用函数时将实际参数复制一份传递到函数中，这样在函数中如果对参数进行修改，将不会影响到实际参数。
```go
func swap(x, y int) {
       x,y = y,x
}

func TestSwap(t *testing.T) {
	a := 1
	b := 2
	swap(a, b)
	fmt.Println(a, b)
}
```
引用传递：是指在调用函数时将实际参数的地址传递到函数中，那么在函数中对参数所进行的修改，将影响到实际参数。
```go
/* 定义相互交换值的函数 */
func swap(x, y *int) {
    var temp int

    temp = *x /* 保存 x 的值 */
    *x = *y   /* 将 y 值赋给 x */
    *y = temp /* 将 temp 值赋给 y*/

}
func TestSwap(t *testing.T) {
	var a, b int = 1, 2
	/*
	   调用 swap() 函数
	   &a 指向 a 指针，a 变量的地址
	   &b 指向 b 指针，b 变量的地址
	*/
    swap(&a, &b)
    fmt.Println(a, b)
}
```
在默认情况下,`Go`语言使用的是值传递，即在调用过程中不会影响到实际参数。
注意1：无论是值传递，还是引用传递，传递给函数的都是变量的副本，不过，值传递是值的拷贝。引用传递是地址的拷贝，一般来说，地址拷贝更为高效。而值拷贝取决于拷贝的对象大小，对象越大，则性能越低。

注意2：`map`、`slice`、`chan`、指针、`interface`默认以引用的方式传递。

不定参数传值 就是函数的参数不是固定的，后面的类型是固定的。（可变参数）

`Golang`可变参数本质上就是`slice`。只能有一个，且必须是最后一个。


# 可变参数
在参数赋值时可以不用用一个一个的赋值，可以直接传递一个数组或者切片，特别注意的是在参数后加上“`…`”即可。
```go
func myfunc(args ...int) {    //0个或多个参数
}

func add(a int, args…int) int {    //1个或多个参数
}

func add(a int, b int, args…int) int {    //2个或多个参数
}
```
注意：其中`args`是一个`slice`，我们可以通过`arg`[index]依次访问所有参数,通过`len(arg)`来判断传递参数的个数.

任意类型的不定参数： 就是函数的参数和每个参数的类型都不是固定的。

用`interface{}`传递任意类型数据是`Go`语言的惯例用法，而且`interface{}`是类型安全的。
```go
func myfunc(args ...interface{}) {
}
```
代码:
```go
func sum(ops...int) int {
    s := 0
    for _,op := range ops {
        s += op
    }
    return s
}
```

# 函数返回值
- "`_`"标识符，用来忽略函数的某个返回值

- `Go`的返回值可以被命名，并且就像在函数体开头声明的变量那样使用。

- 返回值的名称应当具有一定的意义，可以作为文档使用。

- 没有参数的`return语句返回各个返回变量的当前值。这种用法被称作“裸”返回。

- `Golang`返回值不能用容器对象接收多返回值。只能用多个变量，或 "`_`" 忽略。
```go
func test() (int, int) {
    return 1, 2
}
```

- 多返回值可直接作为其他函数调用实参。
- 命名返回参数可看做与形参类似的局部变量，最后由`return`隐式返回。
```go
func add(x, y int) (z int) {
    z = x + y
    return
}
```
- 命名返回参数可被同名局部变量遮蔽，此时需要显式返回。
```go
func add(x, y int) (z int) {
    { // 不能在一个级别，引发 "z redeclared in this block" 错误。
        var z = x + y
        // return   // Error: z is shadowed during return
        return z // 必须显式返回。
    }
}
```
- 命名返回参数允许`defer`延迟调用通过闭包读取和修改。
```go
func add(x, y int) (z int) {
    defer func() {
        z += 100
    }()

    z = x + y
    return
}
```
- 显式`return`返回前，会先修改命名返回参数。
```go
func add(x, y int) (z int) {
    defer func() {
        println(z) // 输出: 203
    }()

    z = x + y
    return z + 200 // 执行顺序: (z = z + 200) -> (call defer) -> (return)
}
```

## 匿名函数
匿名函数是指不需要定义函数名的一种函数实现方式。1958年LISP首先采用匿名函数。

在`Go`里面，函数可以像普通变量一样被传递或使用，`Go`语言支持随时在代码里定义匿名函数。

匿名函数由一个不带函数名的函数声明和函数体组成。匿名函数的优越性在于可以直接使用函数内的变量，不必申明。
```go
func TestAnonymous(t *testing.T) {
	getSqrt := func(a float64) float64 {
		return math.Sqrt(a)
	}
	fmt.Println(getSqrt(4))
}
```
上面先定义了一个名为`getSqrt`的变量，初始化该变量时和之前的变量初始化有些不同，使用了`func`，`func`是定义函数的，可是这个函数和上面说的函数最大不同就是没有函数名，也就是匿名函数。这里将一个函数当做一个变量一样的操作。

`Golang`匿名函数可赋值给变量，做为结构字段，或者在`channel`里传送。
```go
    fn := func() { println("Hello, World!") }
	fn() // output: Hello,World!

	// --- function collection ---
	fns := [](func(x int) int){
		func(x int) int { return x + 1 },
		func(x int) int { return x + 2 },
	}
	println(fns[0](100)) // output : 101

	// --- function as field ---
	d := struct {
		fn func() string
	}{
		fn: func() string { return "Hello, World!" },
	}
	println(d.fn()) // output: Hello,World!

	// --- channel of function ---
	fc := make(chan func() string, 2)
	fc <- func() string { return "Hello, World!" }

	println((<-fc)()) // output : Hello,World!
```

## 闭包
闭包是由函数及其相关引用环境组合而成的实体(即：闭包 = 函数+引用环境)。
“官方”的解释是：所谓“闭包”，指的是一个拥有许多变量和绑定了这些变量的环境的表达式（通常是一个函数），因而这些变量也是该表达式的一部分。
```go
func a() func() int {
	i := 0
	b := func() int {
		i++
		fmt.Println(i)
		return i
	}
	return b
}

func TestClosure(t *testing.T) {
	c := a()
	c()  // output: 1
	c()  // output: 2
	c()  // output: 3

	a() //不会输出i
}
```
闭包复制的是原对象指针，这就很容易解释延迟引用现象。
```go
func test() func() {
    x := 100
    fmt.Printf("x (%p) = %d\n", &x, x)

    return func() {
        fmt.Printf("x (%p) = %d\n", &x, x)
    }
}
```
输出：
```
x (0xc0000a6150) = 100
x (0xc0000a6150) = 100
```
在汇编层 ，`test`实际返回的是`FuncVal`对象，其中包含了匿名函数地址、闭包对象指针。当调 匿名函数时，只需以某个寄存器传递该对象即可。
```
FuncVal { func_address, closure_var_pointer ... }
```
外部引用函数参数局部变量
```go
// 外部引用函数参数局部变量
func add(base int) func(int) int {
    return func(i int) int {
        base += i
        return base
    }
}
```
返回2个闭包
```go
// 返回2个函数类型的返回值
func test(base int) (func(int) int, func(int) int) {
    // 定义2个函数，并返回
    // 相加
    add := func(i int) int {
        base += i
        return base
    }
    // 相减
    sub := func(i int) int {
        base -= i
        return base
    }
    // 返回
    return add, sub
}
```


## 与其它主要编程语言的差异
- 可以有多个返回值
- 所以参数都是值传递:`slice`,`map`,`channel`会有传引用的错觉
- 函数可以作为变量的值
- 函数可以作为参数和返回值

# defer函数
延迟调用defer
- 关键字`defer`用于注册延迟调用。
-  这些调用直到`return`前才被执行。因此，可以用来做资源清理。
- 多个`defer`语句，按先进后出的方式执行。
- `defer`语句中的变量，在`defer`声明时就决定了。

## defer用途:
- 关闭文件句柄
- 锁资源释放
- 数据库连接释放


```go
func TestDefer(t* testing.T) {
    defer func() {
        fmt.Println("clear resources")
    }()

    fmt.Println("started")

    panic("Fatal error") // defer仍会执行

}
```

## 异常处理
`Golang`没有结构化异常，使用`panic`抛出错误，`recover`捕获错误。

异常的使用场景简单描述：`Go`中可以抛出一个`panic`的异常，然后在`defer`中通过`recover`捕获这个异常，然后正常处理。

### panic
- 内置函数
- 假如函数F中书写了`panic`语句，会终止其后要执行的代码，在`panic`所在函数`Fn`内如果
- 存在要执行的`defer`函数列表，按照`defer`的逆序执行
- 返回函数F的调用者`G`，在`G`中，调用函数`Fn`语句之后的代码不会执行，假如函数`G`中存在要执行的`defer`函数列表，按照`defer`的逆序执行
- 直到`goroutine`整个退出，并报告错误

### recover
- 内置函数
- 用来控制一个`goroutine`的`panicking`行为，捕获`panic`，从而影响应用的行为
- 一般的调用建议
    - 在`defer`函数中，通过`recever`来终止一个`goroutine`的`panicking`过程，从而恢复正常代码的执行
    - 可以获取通过`panic`传递的`error`

**注意**:
- 利用`recover`处理`panic`指令，`defer` 必须放在`panic`之前定义，另外`recover`只有在`defer`调用的函数中才有效。否则当`panic`时，`recover`无法捕获到`panic`，无法防止`panic`扩散。
- `recover`处理异常后，逻辑并不会恢复到`panic`那个点去，函数跑到`defer`之后的那个点。
- 多个`defer`会形成`defer`栈，后定义的`defer`语句会被最先调用
```go
func TestPanic(t *testing.T) {
	defer func() {
		if err := recover(); err != nil {
			println(err.(string)) // 将 interface{} 转型为具体类型。
		}
	}()

	panic("panic error!")
}
```
由于`panic`、`recover`参数类型为`interface{}`，因此可抛出任何类型对象。
```
func panic(v interface{})
func recover() interface{}
```

- 向已关闭的通道发送数据会引发`panic`
```go
func TestPanic(t *testing.T) {
	defer func() {
		if err := recover(); err != nil {
			fmt.Println(err)
		}
	}()

	var ch chan int = make(chan int, 10)
	close(ch)
	ch <- 1
}
```
- 延迟调用中引发的错误，可被后续延迟调用捕获，但仅最后一个错误可被捕获。
```go

func except() {
	fmt.Println(recover())
}

func test() {
	defer except()
	panic("test panic")
}

func TestPanic3(t *testing.T) {
	test()
}
```
- 如果需要保护代码段，可将代码块重构成匿名函数，如此可确保后续代码被执 。
```go
func test(x, y int) {
	var z int

	func() {
		defer func() {
			if recover() != nil {
				z = 0
			}
		}()
		panic("test panic")
		z = x / y
		return
	}()

	fmt.Printf("x / y = %d\n", z)
}

func TestPanic4(t *testing.T) {
	test(2, 1)
}
```

**[⬆ 返回顶部](#Problems)**
