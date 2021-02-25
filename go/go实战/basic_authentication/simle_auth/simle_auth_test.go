package main

import (
	"net/http"
	"testing"
)

func TestSimpleAuth(t *testing.T) {
	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		if checkAuth(w, r) {
			w.Write([]byte("hello world!"))
			return
		}

		w.Header().Set("WWW-Authenticate", `Basic realm="MY REALM"`)
		w.WriteHeader(401)
		w.Write([]byte("401 Unauthorized\n"))
	})

	http.ListenAndServe(":8000", nil)
}
