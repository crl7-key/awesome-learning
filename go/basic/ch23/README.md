# sync.Pool 对象缓存

`Pool`用于存储临时对象，它将使用完毕的对象存入对象池中，在需要的时候取出来重复使用，目的是为了避免重复创建相同的对象造成`GC`负担过重,其中存放的临时对象随时可能被`GC`回收掉（如果该对象不再被其它变量引用）。

从`Pool`中取出对象时，如果`Pool`中没有对象，将返回`nil`，但是如果给`Pool.New`字段指定了一个函数的话，`Pool`将使用该函数创建一个新对象返回。

`Pool`可以安全的在多个例程中并行使用，但`Pool `并不适用于所有空闲对象，`Pool`应该用来管理并发的例程共享的临时对象，而不应该管理短寿命对象中的临时对象，因为这种情况下内存不能很好的分配，这些短寿命对象应该自己实现空闲列表。

`Pool`在开始使用之后，不能再被复制！！！！

```go
type Pool struct {

        // New optionally specifies a function to generate
        // a value when Get would otherwise return nil.
        // It may not be changed concurrently with calls to Get.
        New func() interface{}
        // contains filtered or unexported fields
}
```
## sync.Pool 对象获取
> func (p *Pool) Get() interface{}  

作用：从临时对象池中取出对象

- 尝试从私有对象获取
- 私有对象不存在,尝试从当前`Processor`的共享池获取
- 如果当前`Processor`共享池也是空的,那么就尝试去其它`Processor`的共享池获取
- 如果所有子池都是空的,最后就用用户指定的`New`函数产生一个新的对象返回
- 私有对象是协程安全的，共享池是不安全的

## sync.Pool 对象的放回
> func (p *Pool) Put(x interface{})

作用：向临时对象池中存入对象
- 如果私有对象不存在则保持为私有对象
- 如果私有对象存在,放入当前`Processor`子池的共享池中

## 使用sync.Pool
```go
    pool := &syn.Pool {
        New : func() interface {
            return 0
        },
    }

    arr := pool.Get().(int)

    pool,Put(10)
```

## sync.Pool 对象的生命周期
- `GC`会清除`sync.Pool`缓存的对象
- 对象的缓存有效期为下一次`GC`之前


## sync.Pool 总结
- 适合于通过复用,降低复杂对象的创建和`GC`代价
- 协程安全,会有锁的开销
- 生命周期受`GC`影响,不适合于做连接池等,需要自己管理生命周期的资源的池化