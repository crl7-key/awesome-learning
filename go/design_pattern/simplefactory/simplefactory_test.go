package simplefactory

import (
	"fmt"
	"testing"
)

func TestSimpleFactoryForType1(t *testing.T) {
	factory := NewFactory(1)
	d := factory.produce("test")
	if d != "Hi, test" {
		t.Fatal("Type1 test fail")
	}
	fmt.Println(d)
}

func TestSimpleFactoryForType2(t *testing.T) {
	factory := NewFactory(2)
	d := factory.produce("test")
	if d != "Hello, test" {
		t.Fatal("Type1 test fail")
	}
	fmt.Println(d)
}
