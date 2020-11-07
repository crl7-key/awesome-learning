# 单例模式(懒汉式,线程安全)

在`golang`的世界中，没有`private` `public` `static`等关键字，也没有面向对象中类的概念。

**那么`golang`是如何控制访问范围的呢？**
首字母大写,代表对外部可见,首字母小写代表对外部不可见,适用于所有对象,包括函数,方法

`golang中`全局变量
可以使用全局变量,达到`c++`中`static`的效果

`golang`中线程安全的单例模式

使用了`sync`包：
> func (*Once) Do

```go
type SingletonObj struct {
}

var once sync.Once
var obj *SingletonObj

func GetSingleObj()*SingletonObj {
    once.Do(func() {
        fmt.Println("Create Singleton obj")
        obj = &SingletonObj{}
    })
    return obj
}
```

**单例模式操作数据库**
```go
package db

import "fmt"

type repository struct {
    items map[string]string
    mu    sync.RWMutex
}

func (r *repository) Set(key, data string) {
    r.mu.Lock()
    defer r.mu.Unlock()
    r.items[key] = data
}

func (r *repository) Get(key string) (string, error) {
    r.mu.RLock()
    defer r.mu.RUnlock()
    item, ok := r.items[key]
    if !ok {
        return "", fmt.Errorf("The '%s' is not presented", key)
    }
    return item, nil
}

var (
    r    *repository
    once sync.Once
)

func Repository() *repository {
    once.Do(func() {
        r = &repository{
            items: make(map[string]string),
        }
    })

    return r
}
```
