# map声明
```go
m := map[string]int {"one":1,"two":2,"three":3}

m2 := map[string]int{}

m1["one"] = 1

m2 := make(map[string]int,10/* Inital(Capcity) */) 
// map为什么不初始化len?
// len默认初始化为零值，map做不到
```

# map元素的访问
与其它主要编程语言的差异
- 在访问的`key`不存在时,仍会返回零值,不能通过返回`nil`来判断元素是否存在
```go
if v,ok := m["four"];ok {
    t.Log("four : ",v)
} else {
    t.Log("not existing")
}
```

# map遍历
```go
m := map[string]int{"one":1,"two":2,"three":3}
for k,v := range m {
    t.Log(k,v)
}
```

# map与工厂模式
- `map`的`value`可以是一个方法
- 与`Go`的`Dock type`接口方式一起,可以方便的实现单一方法对象的工厂模式
```go
    m := map[int]func(op int) int{}
	m[1] = func(op int) int { return op }
	m[2] = func(op int) int { return op * op }
	m[3] = func(op int) int { return op * op * op }
```

# map实现Set
`Go`的内置集合中没有`Set`实现,可以`map[type]bool`
- 元素的唯一性
- 基本操作
 - 添加元素
 - 判断元素是否存在
 - 删除元素
 - 元素个数