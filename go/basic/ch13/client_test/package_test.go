package client_test

import (
	"fmt"
	series "test/series_test"

	"testing"
)

func TestPackage(t *testing.T) {
	series.GetFibonacciSerie(5)
	fmt.Println(series.Square(5))
}
