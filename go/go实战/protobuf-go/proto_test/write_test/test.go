package main

import (
	"fmt"
	goprotobuf "go-key/go实战/protobuf-go/proto_test"
	"os"

	"google.golang.org/protobuf/proto"
	_ "google.golang.org/protobuf/proto"
)

func main() {

	msg := &goprotobuf.HelloWorld{
		Id:  proto.Int32(996),
		Str: proto.String("hello"),
	}

	path := string("../test.txt")
	f, err := os.Create(path)
	if err != nil {
		fmt.Printf("failed: %s\n", err)
		return
	}

	defer f.Close()
	buffer, err := proto.Marshal(msg)
	f.Write(buffer)
}
