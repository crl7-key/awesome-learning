package main

import (
	"fmt"
	"testing"
	"time"

	"github.com/jasonlvhit/gocron"
)

func task() {
	fmt.Println("I am runnning task.", time.Now())
}

func task2() {
	fmt.Println("I am runnning task2.", time.Now())
}

func TestJasonlvhitGocron(t *testing.T) {
	g := gocron.NewScheduler()
	g.Every(1).Seconds().Do(task)
	g.Every(4).Seconds().Do(task2)

	gc := g.Start() // keep the channel
	go test(g, gc)  // wait
	<-gc            // it will happens if the channel is closed

}

func test(g *gocron.Scheduler, gc chan bool) {
	time.Sleep(8 * time.Second)
	g.Remove(task) //remove task
	time.Sleep(8 * time.Second)
	g.Clear()
	fmt.Println("All task removed")
	close(gc) // close the channel
}
