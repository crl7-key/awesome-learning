# Protobuf

* [目录](#目录)
## 目录
* [什么是protobuf？](#什么是protobuf?)  
* [下载安装](#下载安装)
* [Protobuf语法](#Protobuf语法)
    - [基本规范](#基本规范)
    - [字段规则](#字段规则)
    - [定义Service类型](#定义Service类型)
    - [定义Message类型](#定义Message类型)
    - [添加更多Message类型](#添加更多Message类型)
    - [默认值](#默认值)
    - [枚举(Enum)](#枚举(Enum))
    - [使用其他Message](#使用其他Message)
    - [import导入定义](#import导入定义)
    - [Message嵌套](#Message嵌套)
    - [proto3的Map类型](#proto3的Map类型)
    - [包的使用(Package)](#包的使用(Package))
* [.proto文件编译](#.proto文件编译)
## 什么是protobuf？

`Protocol Buffers`(以下简称PB)是`google`的一种数据交换的格式,它独立于语言,独立于平台。`google`提供了多种语言的实现：`Java`、`c#`、`c++`、`Go`和 `Python`,每一种实现都包含了相应语言的编译器以及库文件。由于它是一种二进制的格式,比使用`xml`进行数据交换快许多。可以把它用于分布式应用之间的数据通信或者异构环境下的数据交换。作为一种效率和兼容性都很优秀的二进制数据传输格式,可以用于诸如网络传输,配置文件,数据存储等诸多领域。    

## 下载安装
[protobuf](https://github.com/protocolbuffers/protobuf/tags)，可以下载最新的版本的`protobuf`进行安装.
例如：  
```sh
# 安装需要的依赖
sudo apt-get install autoconf automake libtool curl make g++ unzip
# 解压 
tar zxvf  protobuf-v3.14.0.tar.gz
# 编译
$ cd protobuf-3.13.0
$ ./autogen.sh # 如果下载的对应语言的包则不需要
$ ./configure
$ make -j4      # 开启4个线程
$ make install
$ ldconfig
$ protoc --version# 查看版本号
```


## Protobuf语法
参考:
[官方资料](https://developers.google.com/protocol-buffers/)

### 基本规范
- 文件以`.proto`做为文件后缀，除结构定义外的语句以分号结尾
- 结构定义可以包含：`message`、`service`、`enum`
- `rpc`方法定义结尾的分号可有可无
- `Message`命名采用驼峰命名方式，字段命名采用小写字母加下划线分隔方式
```protobuf
 message ServerRequest {
    required string required_name = 1;
}
```
- Enums类型名采用驼峰命名方式，字段命名采用大写字母加下划线分隔方式
```protobuf
enum Foo {
    FIRST_VALUE = 1;
    SECOND_VALUE = 2;
}
```
- `Service`与`rpc`方法名统一采用驼峰式命名

### 字段规则
- 字段格式：`限定修饰符` | `数据类型` | `字段名称` | `=` | `字段编码值` | `[字段默认值]`
- 限定修饰符包含 `required`、`optional`、`repeated`
    - `Required`: 表示是一个必须字段，必须相对于发送方，在发送消息之前必须设置该字段的值，对于接收方，必须能够识别该字段的意思。发送之前没有设置`required`字段或者无法识别`required`字段都会引发编解码异常，导致消息被丢弃
    - `Optional`：表示是一个可选字段，可选对于发送方，在发送消息时，可以有选择性的设置或者不设置该字段的值。对于接收方，如果能够识别可选字段就进行相应的处理，如果无法识别，则忽略该字段，消息中的其它字段正常处理。---因为`optional`字段的特性，很多接口在升级版本中都把后来添加的字段都统一的设置为`optional`字段，这样老的版本无需升级程序也可以正常的与新的软件进行通信，只不过新的字段无法识别而已，因为并不是每个节点都需要新的功能，因此可以做到按需升级和平滑过渡
    - `Repeated`：表示该字段可以包含`0~N`个元素。其特性和`optional`一样，但是每一次可以包含多个值。可以看作是在传递一个数组的值
- 数据类型
`Protobuf`定义了一套基本数据类型。几乎都可以映射到`C++\Java`等语言的基础数据类型

<table>
<thead>
<tr>
<th>.proto</th>
<th>C++</th>
<th>Java</th>
<th>Python</th>
<th>Go</th>
<th>Ruby</th>
<th>C#</th>
</tr>
</thead>
<tbody>
<tr>
<td>double</td>
<td>double</td>
<td>double</td>
<td>float</td>
<td>float64</td>
<td>Float</td>
<td>double</td>
</tr>
<tr>
<td>float</td>
<td>float</td>
<td>float</td>
<td>float</td>
<td>float32</td>
<td>Float</td>
<td>float</td>
</tr>
<tr>
<td>int32</td>
<td>int32</td>
<td>int</td>
<td>int</td>
<td>int32</td>
<td>Fixnum or Bignum</td>
<td>int</td>
</tr>
<tr>
<td>int64</td>
<td>int64</td>
<td>long</td>
<td>ing/long<sup>[3]</sup></td>
<td>int64</td>
<td>Bignum</td>
<td>long</td>
</tr>
<tr>
<td>uint32</td>
<td>uint32</td>
<td>int<sup>[1]</sup></td>
<td>int/long<sup>[3]</sup></td>
<td>uint32</td>
<td>Fixnum or Bignum</td>
<td>uint</td>
</tr>
<tr>
<td>uint64</td>
<td>uint64</td>
<td>long<sup>[1]</sup></td>
<td>int/long<sup>[3]</sup></td>
<td>uint64</td>
<td>Bignum</td>
<td>ulong</td>
</tr>
<tr>
<td>sint32</td>
<td>int32</td>
<td>int</td>
<td>intj</td>
<td>int32</td>
<td>Fixnum or Bignum</td>
<td>int</td>
</tr>
<tr>
<td>sint64</td>
<td>int64</td>
<td>long</td>
<td>int/long<sup>[3]</sup></td>
<td>int64</td>
<td>Bignum</td>
<td>long</td>
</tr>
<tr>
<td>fixed32</td>
<td>uint32</td>
<td>int<sup>[1]</sup></td>
<td>int</td>
<td>uint32</td>
<td>Fixnum or Bignum</td>
<td>uint</td>
</tr>
<tr>
<td>fixed64</td>
<td>uint64</td>
<td>long<sup>[1]</sup></td>
<td>int/long<sup>[3]</sup></td>
<td>uint64</td>
<td>Bignum</td>
<td>ulong</td>
</tr>
<tr>
<td>sfixed32</td>
<td>int32</td>
<td>int</td>
<td>int</td>
<td>int32</td>
<td>Fixnum or Bignum</td>
<td>int</td>
</tr>
<tr>
<td>sfixed64</td>
<td>int64</td>
<td>long</td>
<td>int/long<sup>[3]</sup></td>
<td>int64</td>
<td>Bignum</td>
<td>long</td>
</tr>
<tr>
<td>bool</td>
<td>bool</td>
<td>boolean</td>
<td>boolean</td>
<td>bool</td>
<td>TrueClass/FalseClass</td>
<td>bool</td>
</tr>
<tr>
<td>string</td>
<td>string</td>
<td>String</td>
<td>str/unicode<sup>[4]</sup></td>
<td>string</td>
<td>String(UTF-8)</td>
<td>string</td>
</tr>
<tr>
<td>bytes</td>
<td>string</td>
<td>ByteString</td>
<td>str</td>
<td>[]byte</td>
<td>String(ASCII-8BIT)</td>
<td>ByteString</td>
</tr>
</tbody>
</table>

```
+ N 表示打包的字节并不是固定。而是根据数据的大小或者长度
+ 关于 fixed32 和int32的区别。fixed32的打包效率比int32的效率高，但是使用的空间一般比int32多。因此一个属于时间效率高，一个属于空间效率高
```

- 字段名称
    - 字段名称的命名与`C`、`C++`、`Java`等语言的变量命名方式几乎是相同的
    - `protobuf`建议字段的命名采用以下划线分割的驼峰式。例如`first_name`而不是`firstName`

- 字段编码
    - 有了该值，通信双方才能互相识别对方的字段，相同的编码值，其限定修饰符和数据类型必须相同，编码值的取值范围为 `1~2^32（4294967296）`
    - 其中`1~15`的编码时间和空间效率都是最高的，编码值越大，其编码的时间和空间效率就越低，所以建议把经常要传递的值把其字段编码设置为`1-15`之间的值
    - `1900~2000`编码值为`Google protobuf`系统内部保留值，建议不要在自己的项目中使用

- 字段默认值
    - 当在传递数据时，对于`required`数据类型，如果用户没有设置值，则使用默认值传递到对端

### 定义Service类型
如果想要将消息类型用在`RPC`系统中，可以在`.proto`文件中定义一个`RP`C服务接口，`protocol buffer`编译器会根据所选择的不同语言生成服务接口代码    
例如，想要定义一个`RP`C服务并具有一个方法，该方法接收`SearchRequest`并返回一个`SearchResponse`，此时可以在`.proto`文件中进行如下定义：
```protobuf
service SearchService {
    rpc Search (SearchRequest) returns (SearchResponse) {}
}
```
生成的接口代码作为客户端与服务端的约定，服务端必须实现定义的所有接口方法，客户端直接调用同名方法向服务端发起请求，比较麻烦的是，即便业务上不需要参数也必须指定一个请求消息，一般会定义一个空`message`

### 定义Message类型
- 一个`message`类型定义描述了一个请求或响应的消息格式，可以包含多种类型字段.  
例如定义一个搜索请求的消息格式，每个请求包含查询字符串、页码、每页数目
```protobuf
syntax = "proto3";

// SearchRequest 搜索请求
message SearchRequest {
  string query = 1;                 // 查询字符串
  int32 page_number = 2;            // 页码
  int32 result_per_page = 3;        // 每页条数
}
```
- 首行声明使用的`protobuf`版本为`proto3`
- `SearchRequest`消息定义指定了三个字段（名称/值对），每个字段都有一个名称和类型。每个字段声明以分号结尾，`.proto`文件支持双斜线`//`添加单行注释

### 字段类型声明
在上面的示例中，所有字段均为标量类型：两个整数（`page_number`和`result_per_page`）和一个字符串（`query`）。除了基本的标量类型还有复合类型、比如枚举、其它`message`类型等.


### 添加更多Message类型
一个`.proto`文件中可以定义多个消息类型，一般用于同时定义多个相关的消息，例如在同一个`.proto`文件中同时定义搜索请求和响应消息：
```protobuf
syntax = "proto3";

// SearchRequest 搜索请求
message SearchRequest {
  string query = 1;                 // 查询字符串
  int32 page_number = 2;            // 页码
  int32 result_per_page = 3;        // 每页条数
}

// SearchResponse 搜索响应
message SearchResponse {
 ...
}
```

### 默认值
- 对于字符串，默认值为空字符串。
- 对于字节，默认值为空字节。
- 对于布尔值，默认值为`false`。
- 对于数字类型，默认值为零。
- 对于枚举，默认值为第一个定义的枚举值，必须为`0`。
- 对于消息字段，未设置该字段。它的确切值取决于语言。可参考[generated code guide](https://developers.google.com/protocol-buffers/docs/reference/overview)
- 重复字段的默认值为空（通常为相应语言的空列表）

### 枚举(Enum)
在定义消息类型时,希望`message`其中有一个字段仅具有一个预定义的值列表之一.可以通过`enum`在消息定义中为每个可能的值添加一个常量来非常简单地完成此操作。
例如:定义一个搜索请求的消息格式，每个请求包含查询字符串、页码、每页数目,添加了一个带有所有可能值的`enum`被叫项`Corpus`，以及一个`type`字段`Corpus`:
```protobuf
syntax = "proto3";

// SearchRequest 搜索请求
message SearchRequest {
  string query = 1;             // 查询字符串
  int32 page_number = 2;        // 页码
  int32 result_per_page = 3;    // 每页条数
  enum Corpus {
    UNIVERSAL = 0;
    WEB = 1;
    IMAGES = 2;
    LOCAL = 3;
    NEWS = 4;
    PRODUCTS = 5;
    VIDEO = 6;
  }
  Corpus corpus = 4;
}
```
其中,`Corpus`枚举的第一个常量映射为零：每个枚举定义必须包含一个映射为零的常量作为其第一个元素。这是因为：
- 必须有一个零值，以便我们可以使用`0`作为数字默认值。
- 零值必须是第一个元素，以便与`proto2`语义兼容，其中第一个枚举值始终是默认值。

### 使用其他Message
- `message`支持嵌套使用，作为另一`message`中的字段类型
```protobuf
message SearchResponse {
    repeated Result results = 1;
}

message Result {
    string url = 1;
    string title = 2;
    repeated string snippets = 3;
}
```

### import导入定义
- 可以使用`import`语句导入使用其它描述文件中声明的类型
- `protobuf`接口文件可以像`C`语言的`.h`文件一个，分离为多个，在需要的时候通过`import`导入需要对文件。其行为和`C`语言的`#include`或者`java`的`import`的行为大致相同，例如`import "others.proto";`
```protobuf
import "myproject/other_protos.proto";
```
- `protocol buffer`编译器会在 `-I / --proto_path`参数指定的目录中查找导入的文件，如果没有指定该参数，默认在当前目录中查找


### Message嵌套
- 支持嵌套消息，消息可以包含另一个消息作为其字段。也可以在消息内定义一个新的消息
```protobuf
message SearchResponse {
  message Result {
    string url = 1;
    string title = 2;
    repeated string snippets = 3;
  }
  repeated Result results = 1;
}
```
- - 内部声明的`message`类型名称只可在内部直接使用,在外部引用需要前置父级`Message`名称,例如称为`_Parent_._Type_`:
```protobuf
message SomeOtherMessage {
  SearchResponse.Result result = 1;
}
```
- 还可以多层嵌套
```protobuf
message Outer {                  // Level 0
  message MiddleAA {  // Level 1
    message Inner {   // Level 2
      int64 ival = 1;
      bool  booly = 2;
    }
  }
  message MiddleBB {  // Level 1
    message Inner {   // Level 2
      int32 ival = 1;
      bool  booly = 2;
    }
  }
}
```

### proto3的Map类型
- `proto3`支持`map`类型声明
```protobuf
map<key_type, value_type> map_field = N;

message Project {...}
map<string, Project> projects = 1;
```
- 键、值类型可以是内置的类型，也可以是自定义`message`类型
- 字段不支持`repeated`属性
- 不要依赖`map`类型的字段顺序

### 包的使用(Package)
- 在`.proto`文件中使用`package`声明包名，避免命名冲突
```protobuf
syntax = "proto3";
package foo.bar;
message Open {...}
```

- 在其他的消息格式定义中可以使用包名+消息名的方式来使用类型，如
```protobuf
message Foo {
    ...
    foo.bar.Open open = 1;
    ...
}
```
- 在不同的语言中，包名定义对编译后生成的代码的影响不同
    - `C++`中：对应`C++`命名空间，例如`Open`会在命名空间`foo::bar`中
    - `Java` 中：`package`会作为`Java`包名，除非指定了`option jave_package`选项
    - `Python`中：`package`被忽略
    - `Go` 中：默认使用`package`名作为包名，除非指定了`option go_package`选项
    - `JavaNano`中：同`Java`
    - `C#` 中：`package`会转换为驼峰式命名空间，如`Foo.Bar`,除非指定了`option csharp_namespace`选项


## .proto文件编译
- 通过定义好的`.proto`文件生成`Java`,` Python`,` C++`,` Go`,` Ruby`,` JavaNano`, `Objective-C`, or` C#` 代码，需要安装编译器`protoc`。  
运行命令:
```sh
protoc --proto_path=IMPORT_PATH --cpp_out=DST_DIR --java_out=DST_DIR --python_out=DST_DIR --go_out=DST_DIR --ruby_out=DST_DIR --objc_out=DST_DIR --csharp_out=DST_DIR path/to/file.proto
```
- `IMPORT_PATH`:`.proto`解析`import`指令时要在其中查找文件的目录。如果省略，则使用当前目录。可以通过`--proto_pat`h多次传递选项来指定多个导入目录。将按顺序搜索它们。`-I=_IMPORT_PATH_`可以用作的简写形式`--proto_path`。

- 不同语言生成的代码格式不同：
- `C++`: 每个`.proto`文件生成一个`.h`文件和一个`.cc`文件，每个消息类型对应一个类
    - `--cpp_out`在`DST_DIR`中生成`C++`代码`。
    ```
    protoc --proto_path = src --cpp_out = build / gen src / foo.proto src / bar / baz.proto
    ```
- `Java`: 生成一个`.java`文件，同样每个消息对应一个类，同时还有一个特殊的`Builder`类用于创建消息接口
    - `--java_out`在中生成`Java`代码`DST_DIR`。
- `Python`: 姿势不太一样，每个`.proto`文件中的消息类型生成一个含有静态描述符的模块，该模块与一个元类`metaclass`在运行时创建需要的`Python`数据访问类
- `Go`: 生成一个`.pb.go`文件，每个消息类型对应一个结构体
    - `--go_out`在中`DST_DIR`生成`Go`代码。
    ```
    protoc --proto_path=src --go_out=build/gen --go_opt=paths=source_relative src/foo.proto src/bar/baz.proto
    ```
- `Ruby`: 生成一个`.rb`文件的`Ruby`模块，包含所有消息类型
- `JavaNano`: 类似`Java`，但不包含`Builder`类
- `Objective-C`: 每个`.proto`文件生成一个`pbobjc.h`和一个`pbobjc.m`文件
- `C#`: 生成`.cs`文件包含，每个消息类型对应一个类