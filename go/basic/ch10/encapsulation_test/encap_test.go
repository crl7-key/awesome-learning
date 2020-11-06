package encapsulation_test

import (
	"fmt"
	"testing"
	"unsafe"
)

type Employee struct {
	Id   string
	Name string
	Age  int
}

func TestCreateEmployeeObj(t *testing.T) {
	e := Employee{"0", "Bob", 20} // 结构体的初始化
	e2 := Employee{Name: "Mike", Age: 30}
	e3 := new(Employee) // 返回指针
	e3.Id = "2"
	e3.Age = 22
	e3.Name = "Rose"

	fmt.Println(e)
	fmt.Println(e2)
	fmt.Println(e3)
}

func (e Employee) String() string {
	fmt.Printf("Address is %x\n", unsafe.Pointer(&e.Name))
	return fmt.Sprintf("Id:%s Name: %s Age %d", e.Id, e.Name, e.Age)
}

func TestStructoperations(t *testing.T) {
	e := Employee{"0", "Bob", 20} // 结构体的初始化
	fmt.Println(e.String())
}

func (e *Employee) String2() string {
	fmt.Printf("Address is %x\n", unsafe.Pointer(&e.Name))
	return fmt.Sprintf("Id:%s Name: %s Age %d", e.Id, e.Name, e.Age)
}

func TestStructoperations2(t *testing.T) {
	e := &Employee{"0", "Bob", 20}
	fmt.Println(e.String2())
}
