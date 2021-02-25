package main

import (
	"fmt"

	"github.com/kataras/iris"
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
	app.Run(iris.Addr(":8080"))
}
