# package
- 基本复用模块单元,以首字母大写来表明可以被包外代码访问
- 代码的`package`可以和所在的目录不一致
- 统一目录的`Go`代码的`package`要保持一致
- 通过`go get`来获取远程依赖
  - `go get -u` 强制从网络更新远程依赖
- 注意代码在`GitHub`上的组织形式,以适应`go get`
  - 直接以代码路径开始,不要有src

# init方法
- 在`main`被执行前,所有依赖的`package`的`init`方法都会被执行
- 不同的`init`函数按照包导入的依赖关系决定执行顺序
- 每个包可以有多个`init`函数
- 包的每个源文件也可以有多个`init`函数,这点比较特殊

# Go 未解决的依赖问题
- 同一环境下,不同项目使用同一包的不同版本
- 无法管理对包的特定版本的依赖

# vendor路径
 随着`Go 1.5 release`版本的发布,`vendor`目录被添加到除了`GOPATH`和`GOROOT`之外的依赖目录的查找的解决方案。在`Go 1.6`之前，需要手动的设置环境变量


查找依赖包路径的解决方案如下:
- 当前包下的`vendor`目录
- 向上级目录查找,直到找到`src`下的`vendor`目录
- 在`GOPATH`下面查找依赖包
- 在`GOROOT`目录下查找

# 常用的依赖管理工具
```go
godep https://github.com/tools/godep
glide https://github.com/Masterminds/glide
dep https://github.com/golang/dep
```

