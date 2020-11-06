package string_test

import (
	"fmt"
	"strconv"
	"strings"
	"testing"
	"unsafe"
)

func TestString(t *testing.T) {
	var s string // sting 的初始化
	s = "hello"
	fmt.Println(len(s))

	// s[1] = '3' // error string是不可变的byte slice
	s = "\xE4\xB8\xA5" // 可以存储任何二进制数据
	// s = "\xE4\xBA\xB5\xFF"
	fmt.Println(s)

	s = "中"
	fmt.Println(s) // 是byte数

	c := []rune(s) // rune 取出string中的unicode
	fmt.Println(len(c))
	fmt.Println("rune size: ", unsafe.Sizeof(c[0]))

	fmt.Printf("中 unicode : %x\n", c[0])
	fmt.Printf("中 UTF8 : %x\n", s)
}

func TestStringToRune(t *testing.T) {
	s := "中华人民共和国"
	for _, c := range s {
		fmt.Printf("%[1]c %[1]x\n", c)
	}
}

// 切割
func TestStringFn(t *testing.T) {
	s := "A,B,C"
	parts := strings.Split(s, ",")
	for _, part := range parts {
		fmt.Println(part)
	}

	str := strings.Join(parts, "-")
	fmt.Println(str)
}

func TestStringConv(t *testing.T) {
	s := strconv.Itoa(10)
	fmt.Println(s)

	if i, err := strconv.Atoi("10"); err != nil {
		fmt.Println(10 + i)
	}
}
