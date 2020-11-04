package constant_test

import (
	"fmt"
	"testing"
)

const (
	Monday = iota + 1
	Tuesday
	Wednesday
	Thursday
	Friday
	Saturday
	Sunday
)

const (
	Readable = 1 << iota
	Writable
	Executable
)

func TestConstantTry(t *testing.T) {
	t.Log(Monday, Tuesday)
}

func TestConstantTry2(t *testing.T) {
	a := 7 // 0111
	fmt.Print(a&Readable == Readable, a&Writable == Writable, a&Executable == Executable)
	fmt.Println()
	t.Log(a&Readable == Readable, a&Writable == Writable, a&Executable == Executable)
}
