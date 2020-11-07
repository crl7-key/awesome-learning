package util_anyone_reply_test

import (
	"fmt"
	"runtime"
	"testing"
	"time"
)

func runTask(id int) string {
	time.Sleep(10 * time.Millisecond)
	return fmt.Sprintf("The result is from %d", id)
}

func FirstResponse() string {
	numOfRunner := 10
	ch := make(chan string, numOfRunner)
	for i := 0; i < numOfRunner; i++ {
		go func(i int) {
			ret := runTask(i)
			ch <- ret
		}(i)
	}
	return <-ch
}

func AllResponse() string {
	numOfRunner := 10
	ch := make(chan string, numOfRunner)
	for i := 0; i < numOfRunner; i++ {
		go func(i int) {
			ret := runTask(i)
			ch <- ret
		}(i)
	}
	finalRet := ""
	for j := 0; j < numOfRunner; j++ {
		finalRet += <-ch + "\n"
	}
	return finalRet
}

func TestFirstResponse(t *testing.T) {
	fmt.Println("Before: ", runtime.NumGoroutine())
	fmt.Println(FirstResponse())
	fmt.Println(time.Second * 1)
	fmt.Println("After: ", runtime.NumGoroutine())
}

func TestAllResponse(t *testing.T) {
	fmt.Println("Before: ", runtime.NumGoroutine())
	fmt.Println(AllResponse())
	fmt.Println(time.Second * 1)
	fmt.Println("After: ", runtime.NumGoroutine())
}
