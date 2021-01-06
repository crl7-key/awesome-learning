## Go中使用cookie

* [目录](#什么是cookie?)
* [cookie与session的区别](#cookie与session的区别)


### 什么是cookie?

`Cookie`，有时也用其复数形式 `Cookies`，指某些网站为了辨别用户身份、进行`session`跟踪而储存在用户本地终端上的数据（通常经过加密）。定义于`RFC2109`和`2965`中的都已废弃，最新取代的规范是`RFC6265[1]`。（可以叫做浏览器缓存）。 [参考wiki](https://en.wikipedia.org/wiki/HTTP_cookie)

## cookie与session的区别
- `cookie`存储在客户端的纯文本文件
- 用户请求服务器脚本
- 脚本设置`cookie`内容 并通过`http-response`发送`cookie`内容到客户端并保存在客户端本地
- 客户端再次发送`http`请求的时候会将本地的`cookie`内容添加到`http`请求头发送给服务器，服务器端脚本可以调用`cookie`内容
- `session`是存储在服务器的文件,`cookie`内容保存在客户端，存在被客户篡改的情况

`session`和`cookie`是网站浏览中较为常见的两个概念，也是比较难以辨析的两个概念，但它们在浏览需要认证的服务页面以及页面统计中却相当关键。我们先来了解一下`session`和`cookie`怎么来的？考虑这样一个问题：  
如何抓取一个访问受限的网页？如新浪微博好友的主页，个人微博页面等。      
显然，通过浏览器，我们可以手动输入用户名和密码来访问页面，而所谓的“抓取”，其实就是使用程序来模拟完成同样的工作，因此我们需要了解“登陆”过程中到底发生了什么。    
当用户来到微博登陆页面，输入用户名和密码之后点击“登录”后浏览器将认证信息`POST`给远端的服务器，服务器执行验证逻辑，如果验证通过，则浏览器会跳转到登录用户的微博首页，在登录成功后，服务器如何验证我们对其他受限制页面的访问呢？因为`HTTP`协议是无状态的，所以很显然服务器不可能知道我们已经在上一次的`HTTP`请求中通过了验证。当然，最简单的解决方案就是所有的请求里面都带上用户名和密码，这样虽然可行，但大大加重了服务器的负担（对于每个`request`都需要到数据库验证），也大大降低了用户体验(每个页面都需要重新输入用户名密码，每个页面都带有登录表单)。既然直接在请求中带上用户名与密码不可行，那么就只有在服务器或客户端保存一些类似的可以代表身份的信息了，所以就有了`cookie`与`session`。     
`cookie`，简而言之就是在本地计算机保存一些用户操作的历史信息（当然包括登录信息），并在用户再次访问该站点时浏览器通过`HTTP`协议将本地`cookie`内容发送给服务器，从而完成验证，或继续上一步操作。   

## type Cookie
`golang`官方中[Cookie](https://golang.org/search?q=Cookie)结构体的定义
```go
type Cookie struct {
        Name  string
        Value string

        Path       string    // optional
        Domain     string    // optional
        Expires    time.Time // optional
        RawExpires string    // for reading cookies only

        // MaxAge=0 means no 'Max-Age' attribute specified.
        // MaxAge<0 means delete cookie now, equivalently 'Max-Age: 0'
        // MaxAge>0 means Max-Age attribute present and given in seconds
        MaxAge   int
        Secure   bool
        HttpOnly bool
        Raw      string
        Unparsed []string // Raw text of unparsed attribute-value pairs
}
```
## func (*Cookie) String
```go
func (c *Cookie) String() string
```
作用：返回用于`Cookie`头（如果仅设置了`Name`和`Value`）或`Set-Cookie`响应头（如果设置了其他字段）的`cookie`的序列化。如果`c`为`nil`或`c.Name`无效，则返回空字符串

应用：
```go
func read(w http.ResponseWriter, req *http.Request) {

    c, err := req.Cookie("my-cookie")
    if err != nil {
        http.Error(w, http.StatusText(400), http.StatusBadRequest)
        return
    }

    fmt.Fprintln(w, "YOUR COOKIE:", c)
}
```

## func SetCookie
```go
func SetCookie(w ResponseWriter, cookie *Cookie)
```
作用: 将`Set-Cookie`标头添加到提供的`ResponseWriter`标头中。提供的`cookie`必须具有有效的名称。无效的`cookie`可能会被静默删除

应用：
```go
func set(w http.ResponseWriter, req *http.Request) {
    http.SetCookie(w, &http.Cookie{
        Name:  "my-cookie",
        Value: "some value",
    })
    fmt.Fprintln(w, "COOKIE WRITTEN - CHECK YOUR BROWSER")
}
```


## 例子：
```go
package main

import (
    "fmt"
    "net/http"
)

func main() {
    http.HandleFunc("/", set)
    http.HandleFunc("/read", read)
    http.ListenAndServe(":8080", nil)
}

func set(w http.ResponseWriter, req *http.Request) {
    http.SetCookie(w, &http.Cookie{
        Name:  "my-cookie",
        Value: "some value",
    })
    fmt.Fprintln(w, "COOKIE WRITTEN - CHECK YOUR BROWSER")
}

func read(w http.ResponseWriter, req *http.Request) {

    c, err := req.Cookie("my-cookie")
    if err != nil {
        http.Error(w, http.StatusText(400), http.StatusBadRequest)
        return
    }

    fmt.Fprintln(w, "YOUR COOKIE:", c)
}

```