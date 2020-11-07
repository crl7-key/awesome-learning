package share_memory_test

import (
	"fmt"
	"sync"
	"testing"
	"time"
)

// 不是线程安全的
func TestCounter(t *testing.T) {
	counter := 0
	for i := 0; i < 5000; i++ {
		go func() {
			counter++
		}()
	}
	time.Sleep(1 * time.Second)
	fmt.Printf("counter = %d", counter)
}

func TestCounterThreadSafe(t *testing.T) {
	var mute sync.Mutex
	counter := 0
	for i := 0; i < 5000; i++ {
		go func() {
			defer func() {
				mute.Unlock()
			}()
			mute.Lock()
			counter++
		}()
	}
	time.Sleep(1 * time.Second)
	fmt.Printf("counter = %d\n", counter)
}

func TestCounterWaitGroup(t *testing.T) {
	var mute sync.Mutex
	var wg sync.WaitGroup
	counter := 0
	for i := 0; i < 5000; i++ {
		wg.Add(1)
		go func() {
			defer func() {
				mute.Unlock()
			}()
			mute.Lock()
			counter++ // 任务结束
			wg.Done()
		}()
	}
	wg.Wait()
	// time.Sleep(1 * time.Second)
	fmt.Printf("counter = %d\n", counter)
}
