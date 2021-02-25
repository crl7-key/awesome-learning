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
