# 结构体定义
```go
type Employee struct {
    Id string
    Name string
    Age int
}
```

# 行为(方法)定义
与其它主要编程语言的差异
- 第一种定义方式在实例对应方法被调用时,实例的成员会进行值复制
```go
func (e Employee) String()string {
    return fmt.Sprintf("Id:%s Name: %s Age %d",e.Id,e.Name,e.Age)
}
```
- 通常情况下为了避免内存拷贝会使用第二种方式
```go
func (e *Employee) String()string {
    return fmt.Sprintf("Id:%s Name: %s Age %d",e.Id,e.Name,e.Age)
}
```

