# Go实战--Web框架kataras/iris


## 目录
* [kataras/iris简介](#kataras/iris简介)
* [安装](#安装)
* [basic认证](#basic-认证)
* [Markdown](#Markdown)
* [Yaml](#Yaml)
* [Post Json](#Post-Json)
* [TOML](#TOML)
* [Cache](Cache)

## kataras/iris简介
`github`地址:  

[https://github.com/kataras/iris]()


文档地址

[https://docs.iris-go.com/]()


## 安装
```sh
$ go get -u github.com/kataras/iris
```

## 快速开始
新建[`main.go`](iris_demo/main.go)
```golang
package main

import "github.com/kataras/iris"

func main() {
    app := iris.New()
    app.RegisterView(iris.HTML("./views", ".html"))

    app.Get("/", func(ctx iris.Context) {
        ctx.ViewData("message", "Hello world!")
        ctx.View("hello.html")
    })

    app.Run(iris.Addr(":8000"))
}
```

新建`views`文件夹，在`views`中新建[`hello.html`](iris_demo/views/hello.html)
```html
<html>
<head>
    <title>Hello Page</title>
</head>
<body>
    <h1>{{.message}}</h1>
</body>
</html>
```
运行`go run main.go`，在浏览器输入[http://localhost:8000/]()，得到运行结果。


## basic 认证

```golang
package main

import (
	"time"

	"github.com/kataras/iris/v12"
	"github.com/kataras/iris/v12/middleware/basicauth"
)

func NewApp() *iris.Application {
	app := iris.New()

	authConfig := basicauth.Config{
		Users:   map[string]string{"user": "pass", "user2": "password"},
		Realm:   "Authorization Required",
		Expires: time.Duration(30) * time.Minute,
	}

	authentication := basicauth.New(authConfig)

	app.Get("/", func(ctx iris.Context) { ctx.Redirect("/admin") })

	needAuth := app.Party("/admin", authentication)
	{
		// http://localhost:9000/admin
		needAuth.Get("/", handler)
		// http://localhost:9000/admin/profile
		needAuth.Get("/profile", handler)

		// http://localhost:9000/admin/settings
		needAuth.Get("/settings", handler)
	}

	return app
}

func handler(ctx iris.Context) {
	username, password, _ := ctx.Request().BasicAuth()
	ctx.Writef("%s %s:%s", ctx.Path(), username, password)
}

func main() {
	app := NewApp()
	app.Run(iris.Addr(":9000"))
}
```
运行`go run main.go`，在浏览器输入[http://localhost:9000/]()，`basic`认证输入`user: pass`,得到运行结果。

## Markdown
```golang
package main

import (
	"time"

	"github.com/kataras/iris"
	"github.com/kataras/iris/cache"
)

var markdownContents = []byte(`## Hello Markdown

This is a sample of Markdown contents



Features
--------

All features of Sundown are supported, including:

*   **Compatibility**. The Markdown v1.0.3 test suite passes with
    the --tidy option.  Without --tidy, the differences are
    mostly in whitespace and entity escaping, where blackfriday is
    more consistent and cleaner.

*   **Common extensions**, including table support, fenced code
    blocks, autolinks, strikethroughs, non-strict emphasis, etc.

*   **Safety**. Blackfriday is paranoid when parsing, making it safe
    to feed untrusted user input without fear of bad things
    happening. The test suite stress tests this and there are no
    known inputs that make it crash.  If you find one, please let me
    know and send me the input that does it.

    NOTE: "safety" in this context means *runtime safety only*. In order to
    protect yourself against JavaScript injection in untrusted content, see
    [this example](https://github.com/russross/blackfriday#sanitize-untrusted-content).

*   **Fast processing**. It is fast enough to render on-demand in
    most web applications without having to cache the output.

*   **Routine safety**. You can run multiple parsers in different
    goroutines without ill effect. There is no dependence on global
    shared state.

*   **Minimal dependencies**. Blackfriday only depends on standard
    library packages in Go. The source code is pretty
    self-contained, so it is easy to add to any project, including
    Google App Engine projects.

*   **Standards compliant**. Output successfully validates using the
    W3C validation tool for HTML 4.01 and XHTML 1.0 Transitional.

    [this is a link](https://github.com/kataras/iris) `)

func main() {
	app := iris.New()

	app.Get("/", cache.Handler(10*time.Second), writeMarkdown)
	app.Run(iris.Addr(":9000"))
}

func writeMarkdown(ctx iris.Context) {
	println("Handler executed. Content refreshed.")
	ctx.Markdown(markdownContents)
}
```

运行`go run main.go`，在浏览器输入[http://localhost:9000/]()，得到运行结果。

## Yaml
[`iris.yaml`](iris_yaml/iris.yaml)：
```yaml
DisablePathCorrection: false
EnablePathEscape: false
FireMethodNotAllowed: true
DisableBodyConsumptionOnUnmarshal: true
TimeFormat: Mon, 01 Jan 2006 15:04:05 GMT
Charset: UTF-8
```

[`main.go`](iris_yaml/main.go):
```golang
package main

import (
	"github.com/kataras/iris"
)

func main() {
	app := iris.New()
	app.Get("/", func(ctx iris.Context) {
		ctx.HTML("<b>Hello iris!</b>")
	})

	app.Run(iris.Addr(":9000"), iris.WithConfiguration(iris.YAML("./iris.yaml")))
}
```
运行`go run main.go`，在浏览器输入[http://localhost:9000/]()，得到运行结果。

## Post Json
```golang
package main

import (
	"fmt"

	"github.com/kataras/iris/v12"
)

type Company struct {
	Name  string
	City  string
	Other string
}

func MyHandler(ctx iris.Context) {
	c := &Company{}
	if err := ctx.ReadJSON(c); err != nil {
		panic(err.Error())
	} else {
		fmt.Printf("Company: %#v", c)
		ctx.Writef("Company: %#v", c)
	}
}

func main() {
	app := iris.New()
	app.Post("/bind_json", MyHandler)
	app.Run(iris.Addr(":9000"))
}
```
运行`go run main.go`，在终端使用`curl`命令：
```sh
curl -d '{"Name":"username", "City":"ShenZhen", "Other":"shit"}' -H "Content-Type: application/json" -X POST http://localhost:9000/bind_json
```
得到输出结果:
```sh
Company: &main.Company{Name:"username", City:"ShenZhen", Other:"shit"}
```

## TOML
什么是`toml`?  

`toml`也是一种配置文件,是`Tom’s Obvious, Minimal Language`的缩写！

配置文件的使用由来已久，从`.ini`、`XML`、`JSON`、`YAML`再到`TOML`，语言的表达能力越来越强，同时书写便捷性也在不断提升。 `TOML`是前`GitHub CEO`， `Tom Preston-Werner`，于`2013`年创建的语言，其目标是成为一个小规模的易于使用的语义化配置文件格式。`TOML`被设计为可以无二义性的转换为一个哈希表(`Hash table`)。

`github`地址：

[https://github.com/toml-lang/toml]()


例子：
```toml
# This is a TOML document.

title = "TOML Example"

[owner]
name = "Tom Preston-Werner"
dob = 1979-05-27T07:32:00-08:00 # First class dates

[database]
server = "192.168.1.1"
ports = [ 8000, 8001, 8002 ]
connection_max = 5000
enabled = true

[servers]

  # Indentation (tabs and/or spaces) is allowed but not required
  [servers.alpha]
  ip = "10.0.0.1"
  dc = "eqdc10"

  [servers.beta]
  ip = "10.0.0.2"
  dc = "eqdc10"

[clients]
data = [ ["gamma", "delta"], [1, 2] ]

# Line breaks are OK when inside arrays
hosts = [
  "alpha",
  "omega"
]
```
`toml`配置文件不关心空格和缩进。

**规范**
- 大小写敏感
- 必须是`UTF-8`编码
- 不关心空格、缩进
- 使用`#`进行注释

**`Go`中操作`TOML`的优秀开源库**

https://github.com/BurntSushi/toml

https://github.com/pelletier/go-toml

`iris`读取`toml`

新建[`iris.tml`](iris_toml/iris.tml)文件：
```toml
DisablePathCorrection = false
EnablePathEscape = false
FireMethodNotAllowed = true
DisableBodyConsumptionOnUnmarshal = false
TimeFormat = "Mon, 01 Jan 2006 15:04:05 GMT"
Charset = "UTF-8"

[Other]
    MyServerName = "iris"

```
[`main.go`](iris_toml/main.go):
```golang
package main

import (
	"github.com/kataras/iris"
)

func main() {
	app := iris.New()

	app.Get("/", func(ctx iris.Context) {
		ctx.HTML("<b>Hello Iris TOML!</b>")
	})

	app.Run(iris.Addr(":9000"), iris.WithConfiguration(iris.TOML("iris.tml")))
}
```
## Cache
```golang
package main

import (
	"time"

	"github.com/kataras/iris"
	"github.com/kataras/iris/cache"
)

func main() {
	app := iris.New()

	app.Logger().SetLevel("debug")

	app.Get("/hello", cache.Handler(10*time.Second), handler)

	app.Run(iris.Addr(":8080"))
}

func handler(ctx iris.Context) {
	// 点击浏览器的刷新按钮多次，每10秒钟只看到一次println
	println("Handler executed. Content refreshed.")

	ctx.HTML("<h1> Hello, this should be cached. Every 2 minutes it will be refreshed, check your browser's inspector</h1>")
}
```
