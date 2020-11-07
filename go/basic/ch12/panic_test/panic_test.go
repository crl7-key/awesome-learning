package panic_test

import (
	"errors"
	"fmt"
	"testing"
)

func TestPanicVsExit(t *testing.T) {
	// defer func() {
	// 	fmt.Println("Finally!")
	// }()

	defer func() {
		if err := recover(); err != nil {
			fmt.Println("recovered from ", err)
		}
	}()

	fmt.Println("start")

	panic(errors.New("Something wrong!"))
	// os.Exit(-1)
}
