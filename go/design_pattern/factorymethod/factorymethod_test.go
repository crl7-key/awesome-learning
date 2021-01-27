package factorymethod

import (
	"fmt"
	"testing"
)

func Calc(factory OperatorFactory, a, b int) int {
	op := factory.Create()
	op.SetA(a)
	op.SetB(b)
	return op.Result()
}

func TestFactoryMethod(t *testing.T) {
	var (
		factory OperatorFactory
	)

	factory = ProudctABaseFactory{}
	if Calc(factory, 1, 2) != 3 {
		t.Fatal("error with factory method pattern")
	}
	fmt.Println(Calc(factory, 1, 2))

	factory = ProductBBaseFactory{}
	if Calc(factory, 3, 2) != 1 {
		t.Fatal("error with factory method pattern")
	}
	fmt.Println(Calc(factory, 3, 2))
}
