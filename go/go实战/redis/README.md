# golang中使用redis

## 目录
* [何为redis](#何为redis)
* [Redis 优势](#Redis-优势)
* [Redis与其他key-value存储有什么不同？](Redis与其他key-value存储有什么不同？)
* [## redis启动](#redis启动)
* [开源库redigo的使用](#开源库redigo的使用)
    * [连接redis](#连接redis)
    * [读写redis](#读写redis)
    * [检测值是否存在](#检测值是否存在)
    * [删除key](#删除key)
    * [读写json到redis](#读写json到redis)
    * [设置过期时间](#设置过期时间)
* [开源库go-redis/redis的使用](#开源库go-redis/redis的使用)
* [Redis 连接池](#Redis-连接池)

## 何为redis
官网：
[https://redis.io/]()

`Redis is an in-memory database open-source software project implementing a networked, in-memory key-value store with optional durability.`  
`Redis`是一个开源的、使用`C`语言编写的、支持网络交互的、可基于内存也可持久化的`Key-Value`数据库。


## Redis 优势

- 性能极高 – `Redis`能读的速度是`110000`次`/s`,写的速度是`81000`次`/s` 。

- 丰富的数据类型 – `Redis`支持二进制案例的`Strings`,`Lists`,`Hashes`, `Sets`及`Ordered Sets`数据类型操作。

- 原子性 – `Redis`的所有操作都是原子性的，同时`Redis`还支持对几个操作全并后的原子性执行。

- 丰富的特性 – `Redis`还支持`publish/subscribe`, 通知, `key`过期等等特性。

## Redis与其他key-value存储有什么不同？
`Redis`有着更为复杂的数据结构并且提供对他们的原子性操作，这是一个不同于其他数据库的进化路径。`Redis`的数据类型都是基于基本数据结构的同时对程序员透明，无需进行额外的抽象。

`Redis`运行在内存中但是可以持久化到磁盘，所以在对不同数据集进行高速读写时需要权衡内存，因为数据量不能大于硬件内存。在内存数据库方面的另一个优点是，相比在磁盘上相同的复杂的数据结构，在内存中操作起来非常简单，这样`Redis`可以做很多内部复杂性很强的事情。同时，在磁盘格式方面他们是紧凑的以追加的方式产生的，因为他们并不需要进行随机访问。

## redis启动
**启动服务端**  
安装成功后，通过终端键入如下命令：
```
redis-server
```
也可以通过带配置文件启动：
```
redis-server ./redis.conf
```

一切没问题会出现下面的提示:  
```
[11368] 26 Feb 10:10:31.487 # Creating Server TCP listening socket 127.0.0.1:6379: bind: No error
```

**启动客户端**  
新打开一个终端，启动`redis`客户端，键入命令：
```
redis-cli -h 127.0.0.1 -p 6379
```
测试：   
命令返回值

状态回复：pong表示可用
```
127.0.0.1:6379> ping
PONG
127.0.0.1:6379> set mykey abc
OK
127.0.0.1:6379> get mykey
"abc"
```
## 开源库redigo的使用
github地址：
[https://github.com/garyburd/redigo]()

文档地址：
[http://godoc.org/github.com/garyburd/redigo/redis]()

获取：
```sh
go get github.com/garyburd/redigo/redis
```

## 连接redis
```go
package main

import (
	"fmt"
	"github.com/garyburd/redigo/redis"
)

func main() {
    // 连接redis
	c, err := redis.Dial("tcp", "127.0.0.1:6379")
	if err != nil {
		fmt.Println("Connect to redis error", err)
		return
	}
	defer c.Close()
}
```

## 读写redis
这里写入的值永远不会过期
```go
package main

import (
	"fmt"

	"github.com/garyburd/redigo/redis"
)

func main() {
    // 1. 连接redis
	c, err := redis.Dial("tcp", "127.0.0.1:6379")
	if err != nil {
		fmt.Println("Connect to redis error", err)
		return
	}
	defer c.Close()

    // 2. 向redis写入数据
	_, err = c.Do("SET", "mykey", "golang")
	if err != nil {
		fmt.Println("redis set failed:", err)
	}

    // 3. 读取redis数据
	r, err := redis.String(c.Do("GET", "mykey"))
	if err != nil {
		fmt.Println("redis get failed:", err)
	} else {
		fmt.Printf("Get mykey: %v \n", r)
	}
}
```
如何设置过期呢，可以使用`SET`的附加参数：
```go
package main

import (
	"fmt"
	"time"

	"github.com/garyburd/redigo/redis"
)

func main() {
    // 1. 连接redis
	c, err := redis.Dial("tcp", "127.0.0.1:6379")
	if err != nil {
		fmt.Println("Connect to redis error", err)
		return
	}
	defer c.Close()

    // 2. 向redis写入数据,
	_, err = c.Do("SET", "mykey", "golang", "EX", "5")
	if err != nil {
		fmt.Println("redis set failed:", err)
	}

    // 3. 读取redis数据
	r, err := redis.String(c.Do("GET", "mykey"))
	if err != nil {
		fmt.Println("redis get failed:", err)
	} else {
		fmt.Printf("Get mykey: %v \n", r)
	}

	time.Sleep(8 * time.Second)

	r, err = redis.String(c.Do("GET", "mykey"))
	if err != nil {
		fmt.Println("redis get failed:", err)
	} else {
		fmt.Printf("Get mykey: %v \n", r)
	}
}
```
输出：  
```
Get mykey: golang  
redis get failed: redigo: nil returned
```
**批量写入读取**
```
MGET key [key …]
MSET key value [key value …]
```
**批量写入读取对象(Hashtable)**
```
HMSET key field value [field value …]
HMGET key field [field …]
```
## 检测值是否存在
```
EXISTS key
```
```go
package main

import (
	"fmt"

	"github.com/garyburd/redigo/redis"
)

func main() {
	c, err := redis.Dial("tcp", "127.0.0.1:6379")
	if err != nil {
		fmt.Println("Connect to redis error", err)
		return
	}
	defer c.Close()

	_, err = c.Do("SET", "mykey", "golang")
	if err != nil {
		fmt.Println("redis set failed:", err)
	}

	is_key_exit, err := redis.Bool(c.Do("EXISTS", "mykey1"))
	if err != nil {
		fmt.Println("error:", err)
	} else {
		fmt.Printf("exists or not: %v \n", is_key_exit)
	}

}
```
输出：  
```
exists or not: false
```
## 删除key
```
DEL key [key …]
```
```go
package main

import (
	"fmt"

	"github.com/garyburd/redigo/redis"
)

func main() {
	c, err := redis.Dial("tcp", "127.0.0.1:6379")
	if err != nil {
		fmt.Println("Connect to redis error", err)
		return
	}
	defer c.Close()

	_, err = c.Do("SET", "mykey", "golang")
	if err != nil {
		fmt.Println("redis set failed:", err)
	}

	r, err := redis.String(c.Do("GET", "mykey"))
	if err != nil {
		fmt.Println("redis get failed:", err)
	} else {
		fmt.Printf("Get mykey: %v \n", r)
	}

	_, err = c.Do("DEL", "mykey")
	if err != nil {
		fmt.Println("redis delelte failed:", err)
	}

	r, err = redis.String(c.Do("GET", "mykey"))
	if err != nil {
		fmt.Println("redis get failed:", err)
	} else {
		fmt.Printf("Get mykey: %v \n", r)
	}
}
```

输出：
```
Get mykey: golang
redis get failed: redigo: nil returned
```
## 读写json到redis
```go
package main

import (
	"encoding/json"
	"fmt"

	"github.com/garyburd/redigo/redis"
)

func main() {
    // 1. 连接redis
    c, err := redis.Dial("tcp", "127.0.0.1:6379")
	if err != nil {
		fmt.Println("Connect to redis error", err)
		return
	}
	defer c.Close()

    // 2. 设置 key value
	key := "profile"
	imap := map[string]string{"username": "666", "phonenumber": "888"}
	value, _ := json.Marshal(imap)

    // 3. 向redis写入数据
	n, err := c.Do("SETNX", key, value)
	if err != nil {
		fmt.Println(err)
	}
	if n == int64(1) {
		fmt.Println("success")
	}

	var imapGet map[string]string
    // 4. 向redis读取数据
	valueGet, err := redis.Bytes(c.Do("GET", key))
	if err != nil {
		fmt.Println(err)
	}

	errShal := json.Unmarshal(valueGet, &imapGet)
	if errShal != nil {
		fmt.Println(err)
	}
	fmt.Println(imapGet["username"])
	fmt.Println(imapGet["phonenumber"])
}
```



## 设置过期时间
```
EXPIRE key seconds
```
```go
// 设置过期时间为24小时  
n, _ := rs.Do("EXPIRE", key, 24*3600)  
if n == int64(1) {  
    fmt.Println("success")  
}  
```

## 管道

请求/响应服务可以实现持续处理新请求，即使客户端没有准备好读取旧响应。这样客户端可以发送多个命令到服务器而无需等待响应，最后在一次读取多个响应。这就是管道化(`pipelining`)，这个技术在多年就被广泛使用了。距离，很多`POP3`协议实现已经支持此特性，显著加速了从服务器下载新邮件的过程。  
`Redis`很早就支持管道化，所以无论使用任何版本，都可以使用管道化技术

连接支持使用`Send()`，`Flush()`，`Receive()`方法支持管道化操作
```go
Send(commandName string, args ...interface{}) error
Flush() error
Receive() (reply interface{}, err error)
```

`Send`向连接的输出缓冲中写入命令。`Flush`将连接的输出缓冲清空并写入服务器端。`Recevie`按照`FIFO`顺序依次读取服务器的响应。下例展示了一个简单的管道：
```go
c.Send("SET", "foo", "bar")
c.Send("GET", "foo")
c.Flush()
c.Receive() // reply from SET
v, err = c.Receive() // reply from GET
```

`Do`方法组合了`Send`,`Flush`和`Receive`方法。`Do`方法先写入命令，然后清空输出`buffer`，最后接收全部挂起响应包括`Do`方发出的命令的结果。如果任何响应中包含一个错误，`Do`返回错误。如果没有错误，`Do`方法返回最后一个响应。

## 开源库go-redis/redis的使用

github地址：
[https://github.com/go-redis/redis]()

文档地址：
[https://godoc.org/github.com/go-redis/redis]()

获取：
```sh
go get -u github.com/go-redis/redis
```
应用：
```go
package main

import (
	"fmt"

	"github.com/go-redis/redis"
)

func main() {
    // 1. 连接redis
	client := redis.NewClient(&redis.Options{
		Addr:     "127.0.0.1:6379",
		Password: "", // no password set
		DB:       0,  // use default DB
	})

	pong, err := client.Ping().Result()
	fmt.Println(pong, err)

    // 2. 向redis中写入数据
	err = client.Set("key", "value", 0).Err()
	if err != nil {
		panic(err)
	}

    // 3. 向redis中读取数据
	val, err := client.Get("key").Result()
	if err != nil {
		panic(err)
	}
	fmt.Println("key", val)

	val2, err := client.Get("key2").Result()
	if err == redis.Nil {
		fmt.Println("key2 does not exists")
	} else if err != nil {
		panic(err)
	} else {
		fmt.Println("key2", val2)
	}
}
```

## Redis 连接池
- 事先初始化一定数量的连接，放入到连接池
- 当`Go`需要操作`Redis`时，直接从`Redis`连接池取出连接即可
- 这样可以节省获取`Redis`连接的时间，提高效率
```go
package main

import(
	"fmt"
	"github.com/garyburd/redigo/redis"
)

//定义一个全局的pool
var pool *redis.Pool


func init()  {
	pool = &redis.Pool{
		MaxIdle:8,//最大空闲链接数
		MaxActive:0,//表示和数据库的最大链接数，0没有限制
		IdleTimeout:100,//最大空闲时间
		Dial:func()(redis.Conn,error)  {
			return redis.Dial("tcp","localhost:6379")
		},
	}
}

func main() {
	conn := pool.Get()
	defer conn.Close()

	_,err := conn.Do("Set","name","golang")
	if err != nil {
		fmt.Println("conn.Do err=",err)
		return 
	}

	r,err := redis.String(conn.Do("Get","name"))
	if err != nil {
		fmt.Println("conn.Do err=",err)
		return 
	}
	fmt.Println("r=",r)
}
```