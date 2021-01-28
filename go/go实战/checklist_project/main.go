package main

import (
	"net/http"

	"github.com/gin-gonic/gin"
	"github.com/jinzhu/gorm"
	_ "github.com/jinzhu/gorm/dialects/mysql"
)

type Todo struct {
	ID     int    `json:"id"`
	Title  string `json:"title"`
	Status bool   `json:"status"`
}

var (
	DB *gorm.DB
)

func InitMySql() (err error) {
	// 需要创建数据库cheklist : create database checklist character set utf8;
	dsn := "root:123456@tcp(127.0.0.1:3306)/checklist?&parseTime=True&loc=Local"
	DB, err = gorm.Open("mysql", dsn)
	if err != nil {
		panic(err)
	}
	return DB.DB().Ping() //返回一个ping()方法测试链接的结果
}

func main() {
	err := InitMySql()
	if err != nil {
		panic(err)
	}
	defer DB.Close() // 延时关闭数据库

	// 数据绑定（数据迁移）
	DB.AutoMigrate(&Todo{})

	r := gin.Default()
	// 告诉gin框架去哪里找模版文件
	r.LoadHTMLFiles("template/index.html") // 这里根据情况而定，需要自己调试一下这个路径

	// 告诉gin框架模版文件引用的静态文件在哪里
	r.Static("/static", "static")

	// 返回一个页面给请求
	r.GET("/", func(c *gin.Context) {
		c.HTML(http.StatusOK, "index.html", nil)
	})

	// 实现页面上的功能
	// *****************小清单项目具体功能*********************

	v1Group := r.Group("v1")
	{
		//****添加一个待办事项****
		v1Group.POST("/todo", func(c *gin.Context) {
			var todo Todo
			// 1.从请求中拿到数据
			c.BindJSON(&todo)
			// 2.把数据存入数据库
			// 3.返回响应
			err = DB.Create(&todo).Error
			if err != nil {
				c.JSON(http.StatusOK, gin.H{"error": err.Error()})
			} else {
				c.JSON(http.StatusOK, todo)
			}
		})

		// ****查看所有待办事项****
		v1Group.GET("/todo", func(c *gin.Context) {
			// 获取todo表中的所有数据
			// gorm中的db.Find方法
			// 首先要定义一个切片存放查询到的数据，查询成功则返回这个切片
			var todoList []Todo
			err = DB.Find(&todoList).Error
			if err != nil {
				c.JSON(http.StatusOK, gin.H{"error": err.Error()})
			} else {
				c.JSON(http.StatusOK, todoList)
			}
		})
		// ****查看单个待办事项****
		// ****修改某个待办事项****
		v1Group.PUT("/todo/:id", func(c *gin.Context) {
			// 1.从请求中把id拿出来
			id, _ := c.Params.Get("id")
			var todo Todo
			// 2.在todo表中根据请求中的id查询，第一条就是
			err := DB.Where("id=?", id).First(&todo).Error
			if err != nil {
				c.JSON(http.StatusOK, gin.H{"error": err.Error()})
				return
			}
			// 3.与前端操作绑定到一起
			c.BindJSON(&todo)
			// 4.根据前端的操作修改查询到的事项，并保存
			err = DB.Save(&todo).Error
			if err != nil {
				c.JSON(http.StatusOK, gin.H{"error": err.Error()})
			} else {
				c.JSON(http.StatusOK, todo)
			}
		})
		// ****删除某个待办事项****
		v1Group.DELETE("/todo/:id", func(c *gin.Context) {
			// 1.从请求中获取id
			id, ok := c.Params.Get("id")
			if !ok {
				c.JSON(http.StatusOK, gin.H{"error": "无效的id"})
				return
			}
			// 2.从表中根据id删除该数据
			err := DB.Where("id=?", id).Delete(Todo{})
			if err != nil {
				c.JSON(http.StatusOK, gin.H{id: "deleted!"})
			}
		})
	}

	r.Run(":9951")
}
