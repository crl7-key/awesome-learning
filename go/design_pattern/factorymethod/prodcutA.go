package factorymethod

// ProudctABaseFactory 是 ProductA 的工厂类
type ProudctABaseFactory struct{}

func (ProudctABaseFactory) Create() Product {
	return &ProductA{
		Factory: &Factory{},
	}
}

// ProductA Product 的实际加法实现
type ProductA struct {
	*Factory
}

// Result 获取结果
func (o ProductA) Result() int {
	return o.a + o.b
}
