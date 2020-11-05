package operator_test

import (
	"fmt"
	"testing"
)

func TestCompareArray(t *testing.T) {
	a := [...]int{1, 2, 3, 4}
	b := [...]int{1, 3, 4, 5}
	// c := [...]int{1, 2, 3, 4, 5}

	d := [...]int{1, 2, 3, 4}
	fmt.Println(a == b)
	t.Log(a == b)

	// t.Log(a == c)  比较的维数不同,不能进行比较
	fmt.Println(a == d)
	t.Log(a == d)
}
