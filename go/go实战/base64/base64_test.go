package base64

import (
	"encoding/base64"
	"fmt"
	"testing"
)

func TestBase64(t *testing.T) {

	s := "heal the world, make it a better place"

	encodeStd := "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
	s64 := base64.NewEncoding(encodeStd).EncodeToString([]byte(s))

	fmt.Println("base64.NewEncoding(encodeStd).EncodeToString")
	fmt.Println(len(s))
	fmt.Println(len(s64))
	fmt.Println(s)
	fmt.Println(s64)

	// encode
	s64_std := base64.StdEncoding.EncodeToString([]byte(s))
	fmt.Println("base64.StdEncoding.EncodeToString")
	fmt.Println(len(s))
	fmt.Println(len(s64_std))
	fmt.Println(s)
	fmt.Println(s64_std)

	// decode
	s64_decode, err := base64.StdEncoding.DecodeString(s64_std)
	if err != nil {
		fmt.Println(err)
	}
	fmt.Println(string(s64_decode))
}
