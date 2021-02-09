package main

import (
	"errors"
	"fmt"
	"testing"
)

// Create a name type for our new error type
type errorString string

// Implement the error interface.
func (e errorString) Error() string {
	return string(e)
}

// New creates interface values of type error
func New(text string) error {
	return errorString(text)
}

var ErrNameType = New("EOF")
var ErrStructType = errors.New("EOF")

func TestNameTypeError(t *testing.T) {
	if ErrNameType == New("EOF") {
		fmt.Println("Name Type Error")
	}

	if ErrStructType == errors.New("EOF") {
		fmt.Println("struct Type Error")
	}
	// output : Name Type Error
}
