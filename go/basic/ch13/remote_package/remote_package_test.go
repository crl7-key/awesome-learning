package remote

import (
	"fmt"
	"testing"

	cm "github.com/easierway/concurrent_map"
)

// go get -u github.com/easierway/concurrent_map.git
func TestConcurrentMap(t *testing.T) {
	m := cm.CreateConcurrentMap(99)
	m.Set(cm.StrKey("key"), 10)
	fmt.Println(m.Get(cm.StrKey("key")))
}
