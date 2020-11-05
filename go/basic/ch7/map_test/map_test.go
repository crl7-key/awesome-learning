package map_test

import (
	"fmt"
	"testing"
)

func TestInitMap(t *testing.T) {
	m := map[int]int{1: 1, 2: 4, 3: 9}
	fmt.Println(m[2])
	fmt.Println("m len : ", len(m))
	m2 := map[int]int{}
	m2[4] = 16

	fmt.Println("m2 len : ", len(m2))

	m3 := make(map[int]int, 10)
	fmt.Println("m3 len : ", len(m3))
}

func TestAccesNotExistingKey(t *testing.T) {
	m := map[int]int{}
	fmt.Println(m[1])

	m[2] = 0
	fmt.Println(m[2])
	fmt.Println("m len : ", len(m))

	m[3] = 0
	if v, ok := m[3]; ok {
		fmt.Println("key 3 is value is : ", v)
	} else {
		fmt.Println("key 3 is not existing")
	}
}

func TestTravelMap(t *testing.T) {
	m := map[string]int{"one": 1, "two": 2, "three": 3}
	for k, v := range m {
		fmt.Printf("k is %s v is %d \n", k, v)
		t.Log(k, v)
	}
}

func TestMapWithFunValue(t *testing.T) {
	m := map[int]func(op int) int{}
	m[1] = func(op int) int { return op }
	m[2] = func(op int) int { return op * op }
	m[3] = func(op int) int { return op * op * op }
	fmt.Println(m[1](2), m[2](2), m[3](2))
}

func TestMapForSet(t *testing.T) {
	set := map[int]bool{}
	set[1] = true
	n := 3
	if set[n] {
		fmt.Printf("%d is existing\n", n)
	} else {
		fmt.Printf("%d is not existing\n", n)
	}

	set[3] = true
	delete(set, 3)
	n = 3
	if set[n] {
		fmt.Printf("%d is existing\n", n)
	} else {
		fmt.Printf("%d is not existing\n", n)
	}
	fmt.Println(len(set))
}
