# 字符串
与其它主要编程语言的差异
- `string`是数据类型,不是引用或指针类型,不会是一个`nil`
- `string`是只读的`byte slice`，`len`函数可以包含它的`byte`数
- `string`的`byte`数组可以存放任何数据

# Unicode UTF8
- Unicode是一种字符集(code point)
- UTF是unicode的存储实现(转换为字节序列的规则)

# 编码与存储

| 字符 | "中" | 
| ---  | :---: |  
｜Unicode | 0x4E2D|
| UTF-8| 0xE4B8AD|
|string/[]byte| [0xE4,0xB8,0xAd]|

# 常用字符串函数
- [stirngs包](https://golang.org/pkg/strings)
- [strconv包](https://golang.org/pkg/strconv)

