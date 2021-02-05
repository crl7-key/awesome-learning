package code

type Speaker interface {
	// Speak speak action
	Speak()
}

type Student struct {
}

// Speak speak action
func (s *Student) Speak() {
	panic("not implemented") // TODO: Implement
}
