package reflect_test

import (
	"errors"
	"fmt"
	"reflect"
	"testing"
)

func CheckType(v interface{}) {
	t := reflect.TypeOf(v)
	switch t.Kind() {
	case reflect.Float32, reflect.Float64:
		fmt.Println("Float")
	case reflect.Int, reflect.Int32, reflect.Int64:
		fmt.Println("Integer")
	default:
		fmt.Println("Unknown", t)
	}
}

func TestBasicType(t *testing.T) {
	var f float64 = 12
	CheckType(f)
	CheckType(&f)
}

func TestTypeAndValue(t *testing.T) {
	var f int64 = 10
	fmt.Println(reflect.TypeOf(f), reflect.ValueOf(f))
	fmt.Println(reflect.ValueOf(f).Type())
}

type Employee struct {
	Employee string
	Name     string `format:"normal"`
	Age      int
}

func (e *Employee) UpdateAge(newVal int) {
	e.Age = newVal
}
func TestInvokeByName(t *testing.T) {
	e := &Employee{"1", "Mike", 30}
	// 按名字获取成员
	fmt.Printf("Name: value(%[1]v,Type(%[1])T\n", reflect.ValueOf(*e).FieldByName("Name").Type())

	if nameField, ok := reflect.TypeOf(*e).FieldByName("Name"); !ok {
		fmt.Println("Failed to get Name 'Field'.")
	} else {
		fmt.Println("Tag:format ", nameField.Tag.Get("format"))
	}
	reflect.ValueOf(e).MethodByName("UpdateAge").Call([]reflect.Value{reflect.ValueOf(1)})
	fmt.Println("Updated Age: ", e)
}

func TestDeepEqual(t *testing.T) {
	a := map[int]string{1: "one", 2: "two", 3: "three"}
	b := map[int]string{1: "one", 2: "two", 4: "four"}
	// fmt.Println(a == b) // error
	fmt.Println("a == b ?", reflect.DeepEqual(a, b))

	s1 := []int{1, 2, 3}
	s2 := []int{1, 2, 3}
	s3 := []int{2, 3, 1}
	fmt.Println("s1 == s2 ?", reflect.DeepEqual(s1, s2))
	fmt.Println("s1 == s3 ?", reflect.DeepEqual(s1, s3))
}

type Customer struct {
	CookieId string
	Name     string
	Age      int
}

// 万能程序
func fillBySettings(st interface{}, settings map[string]interface{}) error {

	if reflect.TypeOf(st).Kind() != reflect.Ptr {
		// Elem() 获取指针指向的值
		if reflect.TypeOf(st).Elem().Kind() != reflect.Struct { // 如果不是一个结构体类型返回错误
			return errors.New("the first param should be a pointer to the struct type")
		}
	}

	if settings == nil {
		return errors.New("settings is nil.")
	}

	var (
		field reflect.StructField
		ok    bool
	)

	for k, v := range settings {
		if field, ok = (reflect.ValueOf(st).Elem().Type().FieldByName(k)); !ok { // 检查结构体中是否存在field
			continue
		}
		if field.Type == reflect.TypeOf(v) {
			vstr := reflect.ValueOf(st)
			vstr = vstr.Elem()
			vstr.FieldByName(k).Set(reflect.ValueOf(v)) // 存在field进行填充
		}
	}
	return nil
}

func TestFillNameAndAge(t *testing.T) {
	settings := map[string]interface{}{"Name": "Mike", "Age": 40}
	e := Employee{}
	if err := fillBySettings(&e, settings); err != nil {
		fmt.Println(err)
	}

	fmt.Println(e)

	c := new(Customer)
	if err := fillBySettings(c, settings); err != nil {
		fmt.Println(err)
	}
	fmt.Println(*c)
}

