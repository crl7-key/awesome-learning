# reflect.TypeOf vs  reflect.ValueOf
- `reflect.TypeOf`返回类型(`reflect.Type`)
- `reflect.ValueOf`返回值(`reflect.Value`)
- 可以从`reflect.Value`获得类型
- 通过`kind()`来判断类型
```go
const(
    Invalid Kind = iota
    Bool
    Int
    Int8
    Int16
    Int32
    Int64
    Uint
    Uint8
    Uint16
    Uint32
    Uint64
    ....)
```

## 利用反射编写灵活的代码

### 按名字访问结构的成员
```go
reflect.ValueOf(*e).FieldByName("Name")
```

### 按名字访问结构的方法
```go
reflect.ValueOf(e).MethodByName("UpdateAge").Call([]reflect.Value{reflect.ValueOf(1)})
```

### 访问StructTag
```go
	if nameField, ok := reflect.TypeOf(*e).FieldByName("Name"); !ok {
		fmt.Println("Failed to get Name 'Field'.")
	} else {
		fmt.Println("Tag:format ", nameField.Tag.Get("format"))
	}
```
- `Reflect.Type`和`Reflect.Value`都有`FieldByName`方法,需要注意他们的区别

### 关于反射
- 提高了程序的灵活性
- 降低了程序的可读性
- 降低了程序的性能


### 编程中“不安全"行为的危险性
```go
i := 10
f := *(*float64)(unsafe.Pointer(&i))
```
- `go`中不支持强制转换的
