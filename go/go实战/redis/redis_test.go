package redis_test

import (
	"encoding/json"
	"fmt"
	"testing"
	"time"

	"github.com/garyburd/redigo/redis"
)

// Set/Get接口，读写redis
func TestSetGetRedis(t *testing.T) {
	// 1. 连接到redis
	conn, err := redis.Dial("tcp", "127.0.0.1:6379")
	if err != nil {
		fmt.Println("redis.Dial err=", err)
		return
	}
	defer conn.Close()

	// 2. 向redis写入数据
	_, err = conn.Do("Set", "name", "golang")
	if err != nil {
		fmt.Println("set err= \n", err)
		return
	}

	// 3. 读取redis数据
	r, err := redis.String(conn.Do("Get", "name"))
	if err != nil {
		fmt.Println("get err= \n", err)
		return
	} else {
		fmt.Printf("get name: %v \n", r)
	}

	fmt.Println("操作ok", r)
}

// 操作hash
func TestOptHash(t *testing.T) {
	// 1. 连接到redis
	conn, err := redis.Dial("tcp", "127.0.0.1:6379")
	if err != nil {
		fmt.Println("redis.Dial err = ", err)
		return
	}
	defer conn.Close()

	// 2. 向redis写入数据
	// 一个一个放入
	_, err = conn.Do("HSet", "user01", "name", "john")
	if err != nil {
		fmt.Println("set err = ", err)
		return
	}

	_, err = conn.Do("HSet", "user01", "age", 18)
	if err != nil {
		fmt.Println("set err = ", err)
		return
	}

	// 3. 读取redis数据
	r1, err := redis.String(conn.Do("HGet", "user01", "name"))
	if err != nil {
		fmt.Println("hget err = ", err)
		return
	}

	r2, err := redis.Int(conn.Do("HGet", "user01", "age"))
	if err != nil {
		fmt.Println("hget err = ", err)
		return
	}

	fmt.Printf("操作ok r1= %v r2= %v\n", r1, r2)

	// 批量放入
	_, err = conn.Do("HMSet", "user02", "name", "john", "age", 19)
	if err != nil {
		fmt.Println("HMSet err= ", err)
		return
	}
	// 一次读取
	r, err := redis.Strings(conn.Do("HMGet", "user02", "name", "age"))
	if err != nil {
		fmt.Println("hget err= ", err)
		return
	}
	for i, v := range r {
		fmt.Printf("r[%d] = %s \n", i, v)
	}
}

// 批量Set/Get 数据
func TestMSetMGetRedis(t *testing.T) {
	// 1. 连接到redis
	conn, err := redis.Dial("tcp", "127.0.0.1:6379")
	if err != nil {
		fmt.Println("redis.Dial err=", err)
		return
	}
	defer conn.Close()

	// 2. 向redis写入数据
	// 批量放入
	_, err = conn.Do("MSet", "name", "golang", "address", "china")
	if err != nil {
		fmt.Println("MSet err = ", err)
		return
	}
	// 一次读取
	r, err := redis.Strings(conn.Do("MGet", "name", "address"))
	if err != nil {
		fmt.Println("MGet err=", err)
		return
	}

	for i, v := range r {
		fmt.Printf("r[%d] = %s\n", i, v)
	}
}

// 设置过期
func TestSetVaildTime(t *testing.T) {
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

// 检测键值是否存在
func TestIsKeyExit(t *testing.T) {
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

	// 3. 检测值是否存在
	is_key_exit, err := redis.Bool(c.Do("EXISTS", "mykey1"))
	if err != nil {
		fmt.Println("error:", err)
	} else {
		fmt.Printf("exists or not: %v \n", is_key_exit)
	}
}

// 删除key
func TestDelKey(t *testing.T) {
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

	// 3. 向redis读数据
	r, err := redis.String(c.Do("GET", "mykey"))
	if err != nil {
		fmt.Println("redis get failed:", err)
	} else {
		fmt.Printf("Get mykey: %v \n", r)
	}

	// 4. 删除key
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

// 读写json 到 redis
func TestJsonToRedis(t *testing.T) {
	// 1. 连接redis
	c, err := redis.Dial("tcp", "127.0.0.1:6379")
	if err != nil {
		fmt.Println("Connect to redis error", err)
		return
	}
	defer c.Close()

	// 2. 设置 key value
	key := "profile"
	imap := map[string]string{"username": "golang", "phonenumber": "12345678"}
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

func TestOptList(t *testing.T) {
	// 1. 连接到redis
	conn, err := redis.Dial("tcp", "127.0.0.1:6379")
	if err != nil {
		fmt.Println("redis.Dial err=", err)
		return
	}
	defer conn.Close()

	// 2. 向redis写入数据
	_, err = conn.Do("lpush", "herList", "no1:宋江", 30, "no2:卢俊义", 28)
	if err != nil {
		fmt.Println("lpush err=", err)
		return
	}
	// list 先进先出
	r0, err := redis.String(conn.Do("rpop", "herList"))
	if err != nil {
		fmt.Println("MGet err=", err)
		return
	}
	fmt.Println(r0)
	r1, err := redis.String(conn.Do("rpop", "herList"))
	if err != nil {
		fmt.Println("MGet err=", err)
		return
	}
	fmt.Println(r1)

	r2, err := redis.String(conn.Do("rpop", "herList"))
	if err != nil {
		fmt.Println("MGet err=", err)
		return
	}
	fmt.Println(r2)

	r3, err := redis.String(conn.Do("rpop", "herList"))
	if err != nil {
		fmt.Println("MGet err=", err)
		return
	}
	fmt.Println(r3)
	fmt.Println("/* ----------------------------------------------- */")

	values, _ := redis.Values(conn.Do("lrange", "herList", "0", "100"))

	for _, v := range values {
		fmt.Println(string(v.([]byte)))
	}
}

//定义一个全局的pool
var pool *redis.Pool

func init() {
	pool = &redis.Pool{
		MaxIdle:     8,   //最大空闲链接数
		MaxActive:   0,   //表示和数据库的最大链接数，0没有限制
		IdleTimeout: 100, //最大空闲时间
		Dial: func() (redis.Conn, error) {
			return redis.Dial("tcp", "localhost:6379")
		},
	}
}

// 连接池
func TestConnectPools(t *testing.T) {
	conn := pool.Get()
	defer conn.Close()

	_, err := conn.Do("Set", "name", "golang")
	if err != nil {
		fmt.Println("conn.Do err=", err)
		return
	}

	r, err := redis.String(conn.Do("Get", "name"))
	if err != nil {
		fmt.Println("conn.Do err=", err)
		return
	}
	fmt.Println("r=", r)
}
