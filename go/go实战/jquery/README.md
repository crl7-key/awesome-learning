# Go实战--golang中的JQUERY(PuerkitoBio/goquery、从html中获取链接)
`jQuery`是一个快速，小型且功能丰富的`JavaScript`库。通过易于使用的`API`（可在多种浏览器中使用），它使`HTML`文档的遍历和操作，事件处理，动画和`Ajax`等事情变得更加简单。兼具多功能性和可扩展性，`jQuery`改变了数百万人编写`JavaScript`的方式。

`Query`是一个`JavaScript`函数库。
`jQuery `库包含以下特性：
- `HTML`元素选取
- `HTML`元素操作
- `CSS`操作
- `HTML`事件函数
- `JavaScript`特效和动画
- `HTML DOM`遍历和修改
- `AJAX`
- `Utilities`

在`golang`的世界中，
[github.com/PuerkitoBio/goquery]() 这个库就实现了类似`jQuery`的功能，让我们能方便的使用`Go`语言操作`HTML`文档。


如果使用`golang`做爬虫方面的事儿，可能会用到`goquery`。

## PuerkitoBio/goquery
`github`地址：  
[https://github.com/PuerkitoBio/goquery]()


获取：  
```shell
go get github.com/PuerkitoBio/goquery
```

### 创建`Document`对象
`goquery`暴露了两个结构体：`Document`和`Selection`.  
`Document`表示一个`HTML`文档，`Selection`用于像`jQuery`一样操作，支持链式调用。`goquery`需要指定一个`HTML`文档才能继续后续的操作。

### 查找到指定节点
`Selection`有一系列类似`jQuery`的方法，`Document`结构体内嵌了 `*Selection`，因此也能直接调用这些方法。主要的方法是`Selection.Find(selector string)`，传入一个选择器，返回一个新的，匹配到的`*Selection`，所以能够链式调用。

### 属性操作
经常需要获取一个标签的内容和某些属性值，使用`goquery`可以很容易做到


## 官方例子
```go
package main

import (
  "fmt"
  "log"

  "github.com/PuerkitoBio/goquery"
)

func ExampleScrape() {
  doc, err := goquery.NewDocument("http://metalsucks.net")
  if err != nil {
    log.Fatal(err)
  }

  // Find the review items
  doc.Find(".sidebar-reviews article .content-block").Each(func(i int, s *goquery.Selection) {
    // For each item found, get the band and title
    band := s.Find("a").Text()
    title := s.Find("i").Text()
    fmt.Printf("Review %d: %s - %s\n", i, band, title)
  })
}

func main() {
  ExampleScrape()
}
```

输出：
```sh
Review 0: Cavalera Conspiracy - Psychosis
Review 1: Cannibal Corpse - Red Before Black
Review 2: All Pigs Must Die - Hostage Animal
Review 3: Electric Wizard - Wizard Bloody Wizard
Review 4: Trivium - The Sin and the Sentence
```

     

## 获取所有`links`
```go
import (
    "fmt"
    "log"

    "github.com/PuerkitoBio/goquery"
)

func linkScrape() {
    doc, err := goquery.NewDocument("http://www.bilibili.com")
    if err != nil {
        log.Fatal(err)
    }

    doc.Find("body a").Each(func(index int, item *goquery.Selection) {
        linkTag := item
        link, _ := linkTag.Attr("href")
        linkText := linkTag.Text()
        fmt.Printf("Link #%d: '%s' - '%s'\n", index, linkText, link)
    })
}

func main() {
    linkScrape()
}
```

## Convert All HTML Links to reStructuredText via goquery

```go
package main

import (
    "os"
    "strings"
    "text/template"

    "github.com/PuerkitoBio/goquery"
)

const rstLink = "`{{.Text}} <{{.Href}}>`_\n"

type htmlLink struct {
    Text string
    Href string
}

func main() {
    url := "https://www.bilibili.com"

    doc, err := goquery.NewDocument(url)
    if err != nil {
        panic(err)
    }

    tmpl := template.Must(template.New("test").Parse(rstLink))
    doc.Find("a").Each(func(_ int, link *goquery.Selection) {
        text := strings.TrimSpace(link.Text())
        href, ok := link.Attr("href")
        if ok {
            tmpl.Execute(os.Stdout, &htmlLink{text, href})
        }
    })
}

```