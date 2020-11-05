package bitClear_test

import (
	"fmt"
	"testing"
)

const (
	Readable = 1 << iota
	Writable
	Executable
)

func TestBitClear(t *testing.T) {
	a := 7 // 0111
	a = a &^ Readable
	fmt.Print(a&Readable == Readable, a&Writable == Writable, a&Executable == Executable)
	fmt.Println()

	a = a &^ Executable
	fmt.Print(a&Readable == Readable, a&Writable == Writable, a&Executable == Executable)
	fmt.Println()
}
