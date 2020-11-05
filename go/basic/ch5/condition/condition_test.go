package condition_test

import (
	"fmt"
	"testing"
)

func TestIfMultiSec(t *testing.T) {
	if a := 1 == 1; a {
		fmt.Println(" 1 == 1")
	}

}

func TestSwitchMultiCase(t *testing.T) {
	for i := 0; i < 5; i++ {
		switch i {
		case 0, 2:
			fmt.Println("Even")
		case 1, 3:
			fmt.Println("Odd")
		default:
			fmt.Println("it is not 0 - 3")
		}
	}
}

func TestSwitchCondition(t *testing.T) {
	for i := 0; i < 5; i++ {
		switch {
		case i%2 == 0:
			fmt.Println("Even")
		case i%2 == 1:
			fmt.Println("Odd")
		default:
			fmt.Println("it is not 0 - 3")
		}
	}
}
