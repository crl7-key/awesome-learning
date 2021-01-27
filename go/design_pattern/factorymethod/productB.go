package factorymethod

// ProductBBaseFactory 是 ProductB 的工厂类
type ProductBBaseFactory struct {
}

func (ProductBBaseFactory) Create() Product {
	return &ProductB{
		Factory: &Factory{},
	}
}

//ProductB Product 的实际减法实现
type ProductB struct {
	*Factory
}

// Result 获取结果
func (o ProductB) Result() int {
	return o.a - o.b
}
