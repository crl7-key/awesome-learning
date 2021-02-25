## Go实战--basic authentication

## 目录
* [basic认证](#basic认证)
* [通过第三方完成basic认证](#通过第三方完成basic认证)

## basic认证
```
In the context of a HTTP transaction, basic access authentication is a method for a HTTP user agent to provide a user name and password when making a request.
在HTTP事务的上下文中，基本访问身份验证是HTTP用户代理在发出请求时提供用户名和密码的方法。
```
但是这种认证方式有很多的缺点：

虽然基本认证非常容易实现，但该方案建立在以下的假设的基础上，即：客户端和服务器主机之间的连接是安全可信的。特别是，如果没有使用`SSL/TLS`这样的传输层安全的协议，那么以明文传输的密钥和口令很容易被拦截。该方案也同样没有对服务器返回的信息提供保护。

`basic`认证形如：
```sh
Authorization: Basic ZGVtbzpwQDU1dzByZA==
```
### 简单的basic认证
```golang
package main

import (
    "encoding/base64"
    "net/http"
    "strings"
)

func checkAuth(w http.ResponseWriter, r *http.Request) bool {

    s := strings.SplitN(r.Header.Get("Authorization"), " ", 2)
    if len(s) != 2 {
        return false
    }

    b, err := base64.StdEncoding.DecodeString(s[1])
    if err != nil {
        return false
    }

    pair := strings.SplitN(string(b), ":", 2)
    if len(pair) != 2 {
        return false
    }

    return pair[0] == "user" && pair[1] == "pass"
}

func main() {
    http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
        if checkAuth(w, r) {
            w.Write([]byte("hello world!"))
            return
        }

        w.Header().Set("WWW-Authenticate", `Basic realm="MY REALM"`)
        w.WriteHeader(401)
        w.Write([]byte("401 Unauthorized\n"))
    })

    http.ListenAndServe(":8080, nil)
}
```
通过[postman](https://www.postman.com/)工具进行访问：

![postman_test](images/postman_test01.png)
![postman_test](images/postman_test02.png)


## 通过第三方完成basic认证
```sh
go get -u github.com/ant0ine/go-json-rest/rest
```
应用:
```golang
package main

import (
    "log"
    "net/http"

    "github.com/ant0ine/go-json-rest/rest"
)

func main() {
    api := rest.NewApi()
    api.Use(rest.DefaultDevStack...)
    api.Use(&rest.AuthBasicMiddleware{
        Realm: "my realm",
        Authenticator: func(userId string, password string) bool {
            if userId == "user" && password == "pass" {
                return true
            }
            return false
        },
    })
    api.SetApp(rest.AppSimple(func(w rest.ResponseWriter, r *rest.Request) {
        w.WriteJson(map[string]string{"Body": "Hello World!"})
    }))
    log.Fatal(http.ListenAndServe(":8000", api.MakeHandler()))
}
```

**[⬆ 返回顶部](#目录)**