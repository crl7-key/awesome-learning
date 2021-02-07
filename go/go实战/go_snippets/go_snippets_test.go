package testing

import (
	"fmt"
	"io"
	"io/ioutil"
	"os"
	"testing"
	"unicode/utf8"

	. "launchpad.net/gocheck"
)

// 改变string的值
func ChangeString(str string, pos int, ch byte) string {
	c := []byte(str)
	c[pos] = ch
	dst := string(c)
	return dst
}

func TestChangeString(t *testing.T) {
	str := "hello"
	str = ChangeString(str, 0, 'a')
	fmt.Println(str)
}

// 获得子字符串
func GetSubstring(str string, pos int) string {
	substring := str[pos:len(str)]
	return substring
}

func TestGetSubstring(t *testing.T) {
	value := "cat; dog"
	// Take substring from index 4 to length of string.
	fmt.Println(GetSubstring(value, 4))
}

// 遍历字符串
func TraverseString(str string) {
	for key, value := range str {
		fmt.Println(key, value, string(value))
	}
}

func TestTraverseString(t *testing.T) {
	value := "cat;dog"
	TraverseString(value)
}

// 字符串中bytes和characters
func TestRuneCountsInString(t *testing.T) {
	value := "中国"

	i := utf8.RuneCountInString(value)
	fmt.Println(i)

	j := len(value)
	fmt.Println(j)
}

// 在二维数组或切片中查询某个值
func TestSelectValueInArr2Dim(t *testing.T) {
	v := 11

	arr2Dim := [2][2]int{}

	arr2Dim[0][0] = 1
	arr2Dim[0][1] = 11
	arr2Dim[1][0] = 111
	arr2Dim[1][1] = 1111

	found := false

Found:
	for raw := range arr2Dim {
		for column := range arr2Dim[raw] {
			if arr2Dim[raw][column] == v {
				found = true
				break Found
			}
		}
	}
	fmt.Println(found)
}

// 检查map中是否存在某个key
func TestIsKeyExitInMap(t *testing.T) {
	m := map[string]int{"one": 1, "two": 2}
	val, is_key_exit := m["one"]
	fmt.Println(val)
	fmt.Println(is_key_exit)
}

// 检测某个值是否实现了某一接口
func TestCheck(t *testing.T) {
	// 需要添加. launchpad.net/gocheck
	TestingT(t)
}

type MySuite struct{}

var _ = Suite(&MySuite{})

type IFoobar interface {
	foobar()
}

type Foobar struct {
}

func (f *Foobar) foobar() {
}

func (s *MySuite) TestFoobar(c *C) {
	v := Foobar{}
	var i interface{} = v
	_, ok := i.(IFoobar)
	c.Assert(ok, Equals, false)

	var p interface{} = &v
	_, ok = p.(IFoobar)
	c.Assert(ok, Equals, true)
}

// 打开并读取文件
// 使用os.Open

func TestOpenFileRead(t *testing.T) {
	// 打开文件
	file, err := os.Open("input.txt")
	if err != nil {
		panic(err)
	}

	// 退出时关闭文件，并检查其返回的错误
	defer func() {
		if err := file.Close(); err != nil {
			panic(err)
		}
	}()

	// open output file
	fo, err := os.Create("output.txt")
	if err != nil {
		panic(err)
	}
	// close fo on exit and check for its returned error
	defer func() {
		if err := fo.Close(); err != nil {
			panic(err)
		}
	}()

	// 制作缓冲区以保留读取的块
	buf := make([]byte, 1024)
	for {
		// read a chunk from file
		n, err := file.Read(buf)
		if err != nil && err != io.EOF {
			panic(err)
		}
		if n == 0 {
			break
		}

		// write a chunk for fo
		if _, err := fo.Write(buf[:n]); err != nil {
			panic(err)
		}
	}
}

// 打开并读取文件
// 使用outil.ReadFile
func TestOutil(t *testing.T) {
	// read the whole file at once
	b, err := ioutil.ReadFile("input.txt")
	if err != nil {
		panic(err)
	}

	// write the whole body at once
	err = ioutil.WriteFile("output.txt", b, 0644)
	if err != nil {
		panic(err)
	}
}

// 检测某个channel是否被关闭
func TestChannelIsClose(t *testing.T) {
	var ch chan int = make(chan int, 3)
	ch <- 1
	ch <- 2
	ch <- 3
	close(ch)

	for {
		if input, ok := <-ch; !ok {
			fmt.Println("channel closed!")
			break
		} else {
			fmt.Println(input)
		}
	}
}
