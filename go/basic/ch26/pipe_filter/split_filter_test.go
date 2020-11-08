package pipefilter

import (
	"fmt"
	"reflect"
	"testing"
)

func TestSplitFilter(t *testing.T) {
	spliter := NewSplitFilter(",")
	ret, err := spliter.Process("1,2,3")
	if err != nil {
		fmt.Println(err)
	}
	fmt.Println(ret)
	fmt.Println(reflect.TypeOf(ret))
}
