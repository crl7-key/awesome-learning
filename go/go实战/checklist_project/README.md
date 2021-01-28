# 使用gin-gorm实现的一个小清单项目

## 准备工作
需要用到`gin`框架和`gorm`，因此需要在本地安装这两个框架:
```go
go get -u github.com/gin-gonic/gin
```
```go
go get -u github.com/jinzhu/gorm
```

### 配置数据库
开启`mysql`数据库服务,并创建一个数据库（不需要创建表，代码会自动生成）   
登录数据库：
```sh
mysql -u root -p
```
创建数据库(自己命名)
```mysql
> create database checklist character set utf8;
```

## 实现过程

在一个空目录下，创建一个目录(可自己命名),例如：
```sh
mkdir checklist_project
cd checklist_project
```
### 第一步：搭建好架子
在`checklist_project`目录创建一个名为`main.go`的源文件，内容如下：

```go
package main

import (
	"net/http"

	"github.com/gin-gonic/gin"
	"github.com/jinzhu/gorm"
	_ "github.com/jinzhu/gorm/dialects/mysql"
)

func main(){
  r := gin.Default()
  r.GET("/",func(c *gin.Context){
    c.HTML(http.StatusOK,"index.html",nil)
  })
  r.Run(":10000") // ip、端口设置
}
``` 
### 写好数据库连接方法和连接数据库
```go
var (
	DB *gorm.DB
)

func InitMySql() (err error) {
	// 需要创建数据库cheklist : create database checklist character set utf8;
	dsn := "root:123456@tcp(127.0.0.1:3306)/checklist?&parseTime=True&loc=Local" // root 为mysql的用户名 123456为密码
	DB, err = gorm.Open("mysql", dsn)
	if err != nil {
		panic(err)
	}
	return DB.DB().Ping() //返回一个ping()方法测试连接的结果
}
```

### 第三步：连接数据库
```go
func main() {
	err := InitMySql()
	if err != nil {
		panic(err)
	}
    defer DB.Close() // 注意记得延时关闭
    
    r := gin.Default()
    
	r.GET("/", func(c *gin.Context) {
		c.HTML(http.StatusOK, "index.html", nil)
	})
```

#### 一些情况
执行 `go run main.go `。启动后，浏览器访问：[http://localhost:10000/]()   

此时我们打开`127.0.0.1:10000`会发现，啥都没有，因为系统不知道去哪里找模版文件。

```go
     //  告诉gin框架去哪里找模版文件
	r.LoadHTMLFiles("template/index.html") // 这里根据情况而定，需要自己调试一下这个路径
```

此时我们再刷新一下，发现还是有问题，系统不知道上哪找模版文件引用的静态文件，添加静态文件
```go   
    // 告诉gin框架模版文件引用的静态文件在哪里
	r.Static("/static", "static")
    // 这里的前一个是相对路径，表示浏览器要服务器提供的文件，而第二个根目录则是指服务器需要提供的文件放在哪里
```
之后执行，就可以写业务代码了。

## 总结
- 第一步：创建数据库

- 第二步：搭架子

- 第三步：连接数据库<记得延迟关闭数据库连接（defer）

- 第四步：绑定模型（数据迁移）

<完善部分>

告诉`gin`框架去哪里找模版文件 告诉`gin`框架模版文件引用的静态文件去哪里找

- 第五步：分析小清单项目业务逻辑，写好逻辑注释
    - 添加一个待办事项(前端页面填写待办事项，点击提交，会发请求到这里)
    ```go
    v1Group.POST("/todo",func(c *gin.Context){
	1. <从请求中把数据拿出来>
	2. <存入数据库>
	3. <返回响应>
	POST方法
    })
    ```
    - 查看所有待办事项
    ```go
    v1Group.GET("/todo",func(c *gin.Context){

    })
	1. <获取todo表中的所有数据>
	2. <定义一个切片存放查询到的数据>
	3. <查询成功则返回该切片>
	GET方法
    ```
    - 修改某个待办事项
    ```go
    v1Group.PUT("/todo/:id",func(c *gin.Context){
	1.<从请求中把id拿出来>
	2.<在数据库中根据id把数据查询出来>
	3.<将表todo与前端的操作绑定在一起>
	4.<根据前端的操作修改查询到的数据，并保存>
	PUT方法
    })
    ```
    - 删除某个待办事项
    ```go
    v1Group.DELETE("/todo/:id",func(c *gin.Context){
	1.<从请求中将id拿出来>
	2.<在表中根据id将数据删除>
	DELETE方法
    })
    ```