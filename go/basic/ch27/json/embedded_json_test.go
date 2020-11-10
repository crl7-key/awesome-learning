package jsontest

import (
	"encoding/json"
	"fmt"
	"testing"
)

var jsonStr = `{
	"basic_info":{
	"name":"Mike",
	"age":30
	},
	"job_info":{
		"skills":["java","Go","C","C++"]
	}
}`

func TestEmbeddedJson(t *testing.T) {
	e := new(Employee)
	// 解析json
	err := json.Unmarshal([]byte(jsonStr), e)
	if err != nil {
		fmt.Println(err)
	}
	fmt.Println(*e)

	// 序列化
	if v, err := json.Marshal(e); err == nil {
		fmt.Println(string(v))
	} else {
		fmt.Println(err)
	}
}
