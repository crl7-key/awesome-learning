package main

import (
	"fmt"
	"testing"
)

// Positive returns true if the number is positive, false if it is negative
func Positive(n int) bool {
	return n > -1
}

func Check(n int) {
	if Positive(n) {
		fmt.Println(n, " is positive")
	} else {
		fmt.Println(n, " is negative")
	}
}

func TestCheck(t *testing.T) {
	Check(1)
	Check(0)
	Check(-1)
}
