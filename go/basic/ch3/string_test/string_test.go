package string_test

import (
	"fmt"
	"testing"
)

func TestString(t *testing.T) {
	var str string
	t.Log("*" + str + "*") // string是值类型,其默认的初始化值为空字符串
	fmt.Println("*" + str + "*")
	t.Log(len(str))
	fmt.Println(len(str))

	if str == "" {
		fmt.Println("str is \"\" ")
	}
}
