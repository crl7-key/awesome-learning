package iterator_json

import (
	"fmt"
	"os"
	"strings"
	"testing"

	jsoniter "github.com/json-iterator/go"
)

type ColorGroup struct {
	ID     int
	Name   string
	Colors []string
}

func TestJsonIterator(t *testing.T) {

	group := ColorGroup{
		ID:     1,
		Name:   "Reds",
		Colors: []string{"Crimson", "Red", "Ruby", "Maroon"},
	}
	// 序列化
	var json_iterator = jsoniter.ConfigCompatibleWithStandardLibrary
	data, err := json_iterator.Marshal(group)
	if err != nil {
		fmt.Println("error:", err)
	}
	fmt.Println(data)
	os.Stdout.Write(data)

	// 解析
	fmt.Println()
	var buf ColorGroup
	json_iterator.Unmarshal(data, &buf)
	fmt.Printf("%+v\n", buf)

	// 一行代码完成解析
	val := []byte(`{"ID":1,"Name":"Reds","Colors":["Crimson","Red","Ruby","Maroon"]}`)
	id := json_iterator.Get(val, "ID").ToInt()
	name := json_iterator.Get(val, "Name").ToString()
	str := jsoniter.Get(val, "Colors", 0).ToString()
	fmt.Println(id)
	fmt.Println(str)
	fmt.Println(name)

	json := jsoniter.ConfigCompatibleWithStandardLibrary
	reader := strings.NewReader(`{"branch":"beta","change_log":"add the rows{10}","channel":"fros","create_time":"2017-06-13 16:39:08","firmware_list":"","md5":"80dee2bf7305bcf179582088e29fd7b9","note":{"CoreServices":{"md5":"d26975c0a8c7369f70ed699f2855cc2e","package_name":"CoreServices","version_code":"76","version_name":"1.0.76"},"FrDaemon":{"md5":"6b1f0626673200bc2157422cd2103f5d","package_name":"FrDaemon","version_code":"390","version_name":"1.0.390"},"FrGallery":{"md5":"90d767f0f31bcd3c1d27281ec979ba65","package_name":"FrGallery","version_code":"349","version_name":"1.0.349"},"FrLocal":{"md5":"f15a215b2c070a80a01f07bde4f219eb","package_name":"FrLocal","version_code":"791","version_name":"1.0.791"}},"pack_region_urls":{"CN":"https://s3.cn-north-1.amazonaws.com.cn/xxx-os/ttt_xxx_android_1.5.3.344.393.zip","default":"http://192.168.8.78/ttt_xxx_android_1.5.3.344.393.zip","local":"http://192.168.8.78/ttt_xxx_android_1.5.3.344.393.zip"},"pack_version":"1.5.3.344.393","pack_version_code":393,"region":"all","release_flag":0,"revision":62,"size":38966875,"status":3}`)
	decoder := json.NewDecoder(reader)
	params := make(map[string]interface{})
	err = decoder.Decode(&params)
	if err != nil {
		fmt.Println(err)
	} else {
		fmt.Printf("%+v\n", params)
	}
	fmt.Println(params["branch"])
}
