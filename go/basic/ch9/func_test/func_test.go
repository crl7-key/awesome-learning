package func_test

import (
	"fmt"
	"math"
	"math/rand"
	"testing"
	"time"
)

func testFuncMultiValues() (int, int) {
	return rand.Intn(10), rand.Intn(20)
}

func TestFn(t *testing.T) {
	a, b := testFuncMultiValues()
	fmt.Println(a, b)
}

func timeSpent(inner func(op int) int) func(op int) int {
	return func(n int) int {
		start := time.Now()
		ret := inner(n)

		fmt.Println("time spent : ", time.Since(start).Seconds())
		return ret
	}
}

func slowFunc(op int) int {
	time.Sleep(time.Second * 1)
	return op
}

func TestFunc(t *testing.T) {
	a, b := testFuncMultiValues()
	fmt.Println(a, b)

	tsSf := timeSpent(slowFunc)
	fmt.Println(tsSf(10))
}

func swap(a, b int) {
	a, b = b, a
}

/* 定义相互交换值的函数 */
func swap2(x, y *int) {
	var temp int

	temp = *x /* 保存 x 的值 */
	*x = *y   /* 将 y 值赋给 x */
	*y = temp /* 将 temp 值赋给 y*/
}

func TestSwap(t *testing.T) {
	a := 1
	b := 2
	swap(a, b)
	fmt.Println(a, b)
}
func TestSwap2(t *testing.T) {
	var a, b int = 1, 2
	/*
	   调用 swap() 函数
	   &a 指向 a 指针，a 变量的地址
	   &b 指向 b 指针，b 变量的地址
	*/
	swap2(&a, &b)

	fmt.Println(a, b)
}

func test() (int, int) {
	return 1, 2
}

func add(x, y int) int {
	return x + y
}

func sum2(n ...int) int {
	var x int
	for _, i := range n {
		x += i
	}
	return x
}

func add2(x, y int) (z int) {
	z = x + y
	return
}

func add3(x, y int) (z int) {
	{ // 不能在一个级别，引发 "z redeclared in this block" 错误。
		var z = x + y
		// return   // Error: z is shadowed during return
		return z // 必须显式返回。
	}
}

func add4(x, y int) (z int) {
	defer func() { // 延迟调用
		z += 100
	}()

	z = x + y
	return
}

func add5(x, y int) (z int) {
	defer func() {
		println(z) // 输出: 203
	}()

	z = x + y
	return z + 200 // 执行顺序: (z = z + 200) -> (call defer) -> (return)
}

func TestReturn(t *testing.T) {
	x, _ := test()
	println(x)
	println(add(test()))
	println(sum(test()))
	println(add2(1, 2))
	println(add3(1, 2))
	println(add4(1, 2))
	println(add5(1, 2))
}

func sum(ops ...int) int {
	s := 0
	for _, op := range ops {
		s += op
	}
	return s
}

func TestSum(t *testing.T) {
	fmt.Println(sum(1, 2, 3))
	fmt.Println(sum(1, 2, 3, 4, 5))
}

func TestAnonymous(t *testing.T) {
	getSqrt := func(a float64) float64 {
		return math.Sqrt(a)
	}
	fmt.Println(getSqrt(4))

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
}

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
	c()
	c()
	c()

	a() //不会输出i
}

func test2() func() {
	x := 100
	fmt.Printf("x (%p) = %d\n", &x, x)

	return func() {
		fmt.Printf("x (%p) = %d\n", &x, x)
	}
}

func TestFn2(t *testing.T) {
	fn := test2()
	fn()
}

// 外部引用函数参数局部变量
func add6(base int) func(int) int {
	return func(i int) int {
		base += i
		return base
	}
}

func TestFn3(t *testing.T) {
	tmp1 := add6(10)
	fmt.Println(tmp1(1), tmp1(2))
	// 此时tmp1和tmp2不是一个实体了
	tmp2 := add6(100)
	fmt.Println(tmp2(1), tmp2(2))
}

// 返回2个函数类型的返回值
func test3(base int) (func(int) int, func(int) int) {
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

func TestFn4(t *testing.T) {
	f1, f2 := test3(10)
	// base一直是没有消
	fmt.Println(f1(1), f2(2))
	// 此时base是9
	fmt.Println(f1(3), f2(4))
}

func TestPanic(t *testing.T) {
	defer func() {
		if err := recover(); err != nil {
			println(err.(string)) // 将 interface{} 转型为具体类型。
		}
	}()

	panic("panic error!")
}

func TestPanic2(t *testing.T) {
	defer func() {
		if err := recover(); err != nil {
			fmt.Println(err)
		}
	}()

	var ch chan int = make(chan int, 10)
	close(ch)
	ch <- 1
}

func except() {
	fmt.Println(recover())
}

func test7() {
	defer except()
	panic("test panic")
}

func TestPanic3(t *testing.T) {
	test7()
}

func test8(x, y int) {
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
	test8(2, 1)
}
