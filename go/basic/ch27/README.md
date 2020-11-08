# 内置的JSON解析
利用反射实现,通过`FiledTag`来标识对应的`json`值
```go
type BasicInfo struct {
    Name string `json:"name"`
    Age int `json:"age"`
}

type JobInfo struct {
    Skills []string `json:"skills"`
}

type Employee struct {
    BasicInfo  BasicInfo `json:"basic_info"`
    JobInfo    JobInfo   `json:"job_info"`
}
```

`encoding/json` 是`Go`语言自带的`JSON`转换库
Marshal
> func Marshal(v interface{}) ([]byte, error)

把对象转换为JSON:
- 布尔型转换为`JSON`后仍是布尔型, 如`true` -> `true`
- 浮点型和整数型转换后为`JSON`里面的常规数字，如`1.23` -> `1.23`
- 字符串将以`UTF-8`编码转化输出为`Unicode`字符集的字符串，特殊字符比如`<`将会被转义为`\u003c`
- 数组和切片被转换为`JSON`里面的数组，`[]byte`类会被转换为`base64`编码后的字符串，`slice`的零值被转换为`null`
- 结构体会转化为`JSON`对象，并且只有结构体里边以大写字母开头的可被导出的字段才会被转化输出，而这些可导出的字段会作为`JSON`对象的字符串索引
- 转化一个`map`类型的数据结构时，该数据的类型必须是`map[string]T`（`T `可以是`encoding/json` 包支持的任意数据类型）

Unmarshal
> func Unmarshal(data [] byte, v interface{}) error

把`JSON`转换回对象的方法:
这个函数会把传入的`data`作为一个`JSON`来进行解析，解析后的数据存储在参数`v`中。这个参数`v`也是任意类型的参数（但一定是一个类型的指针），原因是我们在是以此函数进行`JSON`解析的时候，这个函数不知道这个传入参数的具体类型，所以它需要接收所有的类型。


## 更快的JSON解析easyjson
`EasyJson`采用代码生产而非反射

安装
```
go get -u github.com/mailru/easyjson/...
```

使用
`easyjson -all <file>.go`

例如：
`root@MacBook-Pro ~ % /Users/root/go/bin/easyjson -all struct_def.go`
相应的会生成对应的`xxxx_json.go`和`xxx_json_test.go`文件
