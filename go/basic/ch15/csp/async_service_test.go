package csp

import (
	"fmt"
	"testing"
	"time"
)

func service() string {
	time.Sleep(time.Microsecond * 50)
	return "Done"
}

func otherTask() {
	fmt.Println("working on something else")
	time.Sleep(time.Microsecond * 100)
	fmt.Println("Task is done.")
}

func TestService(t *testing.T) {
	fmt.Println(service())
	otherTask()
}

func AsyncService() chan string {
	// rech := make(chan string)
	reCh := make(chan string, 1)

	go func() {
		ret := service()
		fmt.Println("returned result.")
		reCh <- ret
		fmt.Println("service exited")
	}()
	return reCh
}

func TestAsyncService(t *testing.T) {
	reCh := AsyncService()
	otherTask()
	fmt.Println(<-reCh)
	time.Sleep(time.Second * 1)
}
