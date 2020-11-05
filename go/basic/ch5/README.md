#  循环
与其它主要编程语言的差异
- `GO`语言仅支持循环关键字`for`
```go
for( j := 7 ; j <= 9; j ++)
```

- 如果表示`while`条件循环`while(n < 5)`, `Go`中可以这样写:
```go
n := 0
for n < 5 {
    n++
    fmt.Println(n)
}
```

- 如果表♾循环`while(true)`, `Go`中可以这样写:
```go
n := 0
for {
    ....
}
```

# if 条件
```go
if condition {
    // code to be executed if condition is true
} else {
    // code to be executed if condition is false
} 


if condition - 1 {
    // code to be executed if condition - 1 is true
} else if condition - 2 {
    // code to be executed if condition - 2 is true
} else {
    // code to be executed if both condition1 and condition2 are  false
}
```
- `else if` 和 `else` 必须写在花括号之后

# switch 条件
```go
switch os := runtime.GOOS; os {
    case "darwin":
        fmt.Println("OS X.")
        // break
    case "linux":
        fmt.Println("Linux")
    default:
        // freebsa,openbsd,
        // plan9,windows...
        fmt.Printf("%s",os)
}
```

```go
switch {
    case 0 < Num && Num <= 3:
        fmt.Printf("0 - 3")
    case 4 < Num && Num <= 6:
        fmt.Printf("4 - 6")
    case 7 <= Num && Num <= 9:
        fmt.Printf("7 - 9")
}
```
与其它主要编程语言的差异:
- 条件表达式不限制位常量或者整数
- 单个case中,可以出现多个结果选项,使用逗号分隔;
- 与C语言等规则相反,`Go`语言不需要`break`来明确退出一个`case`;
- 可以不设定`switch`之后的条件表达式,在此种情况下,整个`switch`结构与多个`if ... else..`的逻辑作用等同