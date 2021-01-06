package cookie_test

import (
	"fmt"
	"net/http"
	"testing"
)

func set(w http.ResponseWriter, req *http.Request) {
	http.SetCookie(w, &http.Cookie{
		Name:  "my-cookie",
		Value: "some value",
	})
	fmt.Fprintln(w, "COOKIE WRITTEN - CHECK YOUR BROWSER")
}

func read(w http.ResponseWriter, req *http.Request) {

	c, err := req.Cookie("my-cookie")
	if err != nil {
		http.Error(w, http.StatusText(400), http.StatusBadRequest)
		return
	}

	fmt.Fprintln(w, "YOUR COOKIE:", c)
}

func TestCookie(t *testing.T) {
	http.HandleFunc("/", set)
	http.HandleFunc("/read", read)
	http.ListenAndServe(":8080", nil)
}
