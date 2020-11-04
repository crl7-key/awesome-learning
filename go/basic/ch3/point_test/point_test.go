package point_test

import "testing"

func TestPoint(t *testing.T) {
	a := 1
	ptr := &a
	// ptr = ptr + 1  error
	t.Log(a, ptr)
	t.Logf("%T %T", a, ptr)
}


