package pipefilter

import (
	"fmt"
	"testing"
)

func TestStraightPipeline(t *testing.T) {
	spliter := NewSplitFilter(",")
	converter := NewToIntFilter()
	sum := NewSumFilter()
	sp := NewStraightPipeline("p1", spliter, converter, sum)
	ret, err := sp.Process("1,2,3")
	if err != nil {
		fmt.Println(err)
	}
	if ret != 6 {
		fmt.Printf("The expected is 6,but the actual is %d\n", ret)
	}
	fmt.Println(ret)
}
