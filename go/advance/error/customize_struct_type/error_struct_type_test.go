package main

import (
	"fmt"
	"testing"
)

type errorString struct {
	s string
}

func (e errorString) Error() string {
	return e.s
}

func NewError(text string) error {
	return errorString{text}
}

var ErrType = NewError("EOF")

func TestNewError(t *testing.T) {
	if ErrType == NewError("EOF") {
		fmt.Println("Error:", ErrType) // output ： Error: EOF
	}
}
