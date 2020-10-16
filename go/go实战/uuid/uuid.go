package main

import (
	"fmt"

	"github.com/google/uuid"
)

//RandomID RandomID
func RandomID() string {
	return uuid.New().String()
}

// FromString FromString
func FromString(s string) (uuid.UUID, error) {
	return uuid.Parse(s)
}

func main() {

	uuid := RandomID()
	fmt.Println("uuid is : ", uuid)
  
	// 解析
	u2, err := FromString("3d57ae27-6cc4-40c7-b18f-e087b77daded")
	if err != nil {
		fmt.Printf("Something gone wrong: %s", err)
		return
	}
	fmt.Printf("Successfully parsed: %s", u2)
}
