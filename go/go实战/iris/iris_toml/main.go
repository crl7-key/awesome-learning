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
