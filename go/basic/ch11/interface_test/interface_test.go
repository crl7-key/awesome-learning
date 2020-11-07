package interface_test

import (
	"fmt"
	"testing"
)

type Programmer interface {
	WriteHelloWorld() string
}

type GoProgrammer struct {
}

func (g *GoProgrammer) WriteHelloWorld() string {
	return "Hello World"
}

func TestClient(t *testing.T) {
	var p Programmer
	p = new(GoProgrammer)
	fmt.Println(p.WriteHelloWorld())
}

type Cat struct{}

func (c Cat) Say() string { return "喵喵喵" }

type Dog struct{}

func (d Dog) Say() string { return "汪汪汪" }

func TestAnimal(t *testing.T) {
	c := Cat{}
	fmt.Println("猫:", c.Say())
	d := Dog{}
	fmt.Println("狗:", d.Say())
}

// Sayer接口
type Sayer interface {
	Say() string
}

func TestAnimalInterface(t *testing.T) {
	var speaker Sayer // 声明一个Sayer类型的变量speaker
	c := Cat{}        // 实例化一个Cat
	d := Dog{}        // 实例化一个Dog

	speaker = c                // 可以把Cat实例化直接赋值给speaker
	fmt.Println(speaker.Say()) // 喵喵喵

	speaker = d                // 可以把Dog实例化直接赋值给speaker
	fmt.Println(speaker.Say()) // 汪汪汪
}

type People interface {
	Speak(string) string
}

type Student struct{}

func (stu *Student) Speak(think string) (talk string) {
	if think == "sb" {
		talk = "你是个大帅比"
	} else {
		talk = "您好"
	}
	return
}

func TestFn(t *testing.T) {
	var peo People
	stu := Student{}

	peo = &stu
	think := "bitch"
	fmt.Println(peo.Speak(think))
}
