package main

import (
	"fmt"
	"io"
	"os"

	goprotobuf "github.com/crl7/go/go实战/protobuf-go/proto_test"

	"google.golang.org/protobuf/proto"
)

func CheckError(err error) {
	if err != nil {
		fmt.Println(err.Error())
		os.Exit(-1)
	}
}
func main() {
	path := string("../test.txt")
	file, err := os.Open(path)
	if err != nil {
		fmt.Printf("failed: %s\n", err)
		return
	}

	defer file.Close()
	fi, err := file.Stat()
	CheckError(err)
	buffer := make([]byte, fi.Size())
	_, err = io.ReadFull(file, buffer)
	CheckError(err)

	msg := &goprotobuf.HelloWorld{}
	err = proto.Unmarshal(buffer, msg)
	CheckError(err)

	fmt.Printf("read: %s\n", msg.String())
}
