package slice_test

import (
	"fmt"
	"testing"
)

func TestSliceInit(t *testing.T) {
	var s []int
	fmt.Println(len(s), cap(s))

	s = append(s, 1)
	fmt.Println(len(s), cap(s))

	s1 := []int{1, 2, 3, 4}
	fmt.Println(len(s1), cap(s1))

	// make(type,len,cap)
	s2 := make([]int, 3, 5)
	fmt.Println(len(s2), cap(s2))
	// fmt.Println(s2[0], s2[1], s2[2], s2[3], s2[4]) // error index out of range
	s2 = append(s2, 1)
	fmt.Println(s2[0], s2[1], s2[2], s2[3])
	fmt.Println(len(s2), cap(s2))
}

func TestSiceGrowing(t *testing.T) {
	s := []int{}
	for i := 0; i < 10; i++ {
		s = append(s, i)
		fmt.Println(len(s), cap(s))
	}
}

func TestSliceShareMemory(t *testing.T) {
	year := []string{"Jan", "Feb", "Mar", "Apr", "Jun", "Jul", "Aug", "Sep",
		"Oct", "Nov", "Dec"}
	Q2 := year[3:6]
	fmt.Println(Q2)
	fmt.Println(len(Q2), cap(Q2))
}

func TestSliceCompare(t *testing.T) {
	// 切片只能和nil 进行比较
	// a := []int{1, 2, 3, 4}
	// b := []int{1, 2, 3, 4}
	// if a == b {
	// 	fmt.Println("equal")
	// }
}
