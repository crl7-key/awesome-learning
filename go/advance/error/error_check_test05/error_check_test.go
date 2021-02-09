package main

import (
	"fmt"
	"testing"
)

// Positive returns true if the number is positive,false if it is negative
// In the case that n is 0, Positive will panic
func Positive(n int) bool {
	if n == 0 {
		panic("undefined")
	}
	return n > -1
}

func Check(n int) {
	defer func() {
		if recover() != nil {
			fmt.Println("is neither")
		}
	}()

	if Positive(n) {
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
