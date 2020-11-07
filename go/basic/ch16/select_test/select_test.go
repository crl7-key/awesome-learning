package select_test

import (
	"fmt"
	"testing"
	"time"
)

func service() string {
	time.Sleep(time.Microsecond * 500)
	return "Done"
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

func TestSelect(t *testing.T) {
	select {
	case ret := <-AsyncService():
		fmt.Println(ret)
	case <-time.After(time.Microsecond * 100):
		fmt.Println("time out")
	}
}
