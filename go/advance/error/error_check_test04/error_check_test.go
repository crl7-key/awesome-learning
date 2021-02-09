package main

import (
	"fmt"
	"testing"
)

// If the result not nil, the result is true if the number is
// positive,false if it is negative
func Positive(n int) *bool {
	if n == 0 {
		return nil
	}
	r := n > -1
	return &r
}

func Check(n int) {
	pos := Positive(n)
	if pos == nil {
		fmt.Println(n, "is neither")
		return
	}
	if *pos {
		fmt.Println(n, "is positive")
	} else {
		fmt.Println(n, "is negative")
	}
}

func TestCheck(t *testing.T) {
	Check(1)
	Check(0)
	Check(-1)
}
