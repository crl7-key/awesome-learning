package factorymethod

// Product 是被封装的实际类接口
type Product interface {
	SetA(int)
	SetB(int)
	Result() int
}

// Factory Product 接口实现的基类，封装公用方法
type Factory struct {
	a, b int
}

// OperatorFactory 是工厂接口
type OperatorFactory interface {
	Create() Product
}

// SetA 设置 A
func (f *Factory) SetA(a int) {
	f.a = a
}

// SetB 设置 B
func (f *Factory) SetB(b int) {
	f.b = b
}
