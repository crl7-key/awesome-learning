# 基本数据类型
```
bool
string
int     int8    int16   int32   int64
uint    uint8   uint16  uint32  uint63    uintptr
byte    // alias for uint8
rune    // alias for int32,represents a Unicode code point
float32  float64
complex64   complex128
```

# 类型转化
与其它主要编程语言的差异
- `Go`语言不允许隐式类型转换
- 别名和原有类型也不能进行隐式类型转换

# 类型的预定义值
- math.MaxInt64
- math.MaxFloat64
- math.MaxUint32

# 指针类型
与其它主要编程语言的差异
- 不支持指针运算
- `string`是值类型,其默认的初始化值为空字符串,而不是`nil`


