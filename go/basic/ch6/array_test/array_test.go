package array_test

import (
	"fmt"
	"testing"
)

func TestArrayInt(t *testing.T) {
	var arr [3]int

	arr1 := [4]int{1, 2, 3, 4}

	arr2 := [...]int{1, 3, 4, 5}

	fmt.Println(arr[1], arr[2])
	fmt.Println(arr1, arr2)
}

func TestArrayTravel(t *testing.T) {
	arr := [...]int{1, 3, 4, 5}
	for i := 0; i < len(arr); i++ {
		fmt.Println(arr[i])
	}

	for index, e := range arr {
		fmt.Println(index, e)
	}
	for _, e := range arr {
		fmt.Println(e)
	}
}

func TestArraySection(t *testing.T) {
	arr := [...]int{1, 3, 4, 5}
	arr_sec := arr[:3]
	fmt.Println(arr_sec)

	arr_sec2 := arr[3:]
	fmt.Println(arr_sec2)

	// arr_sec3 := arr[:-1] // error

}
