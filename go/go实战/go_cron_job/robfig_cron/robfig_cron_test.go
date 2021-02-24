package main

import (
	"fmt"
	"testing"

	"github.com/robfig/cron"
)

func TestRobfigCron(t *testing.T) {
	i := 0
	c := cron.New()
	// 每分钟执行一次
	spec := "0 */1 * * * *"
	c.AddFunc(spec, func() {
		i++
		t.Log("execute per second ", i)
	})
	c.Start()
	select {}
}

func myFunc() {
	fmt.Println("execute")
}

func TestRobfigCron2(t *testing.T) {
	spec := "2,10 9-12 * * *" // 每天上午9点到12点的第2和第10分钟执行
	c := cron.New()
	c.AddFunc(spec, myFunc)
	c.Start()
	select {}
}
