package simplefactory

import (
	"fmt"
)

// Factory is interface
type Factory interface {
	produce(some string) string
}

// NewFactory return Factory instance by type
func NewFactory(t int) Factory {
	if t == 1 {
		return &ProductA{}
	} else if t == 2 {
		return &ProductB{}
	}
	return nil
}

// ProductA is one of Product implement
type ProductA struct {
}

// return hi to some
func (*ProductA) produce(some string) string {
	return fmt.Sprintf("Hi, %s", some)
}

// ProductB is another Product implement
type ProductB struct {
}

// return hello to some
func (*ProductB) produce(some string) string {
	return fmt.Sprintf("Hello, %s", some)
}
