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
