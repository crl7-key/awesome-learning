


# 实时读取文件内容

生命不止,继续go go go!!!

这里介绍一下,在做日志分析的时候,需要实时的获取日志里面的内容



## hpcloud/tail 
```
go get github.com/hpcloud/tail/...
```


## Example

```go
package main

import (
    "fmt"
    "time"

    "github.com/hpcloud/tail"
)

func main() {
    fileName := "./my.log"
    config := tail.Config{
        ReOpen:    true,                                 // 重新打开
        Follow:    true,                                 // 是否跟随
        Location:  &tail.SeekInfo{Offset: 0, Whence: 2}, // 从文件的哪个地方开始读
        MustExist: false,                                // 文件不存在不报错
        Poll:      true,
    }
    tails, err := tail.TailFile(fileName, config)
    if err != nil {
        fmt.Println("tail file failed, err:", err)
        return
    }
    var (
        line *tail.Line
        ok   bool
    )
    go func() {
		for {
			line, ok = <-tails.Lines
			if !ok {
				fmt.Println("tail file close reopen, filename:%s\n", tails.Filename)
				time.Sleep(time.Second)
				continue
			}
			fmt.Println("line:", line.Text)
			//TODO
		}
	}()
}
```

在同级目录下面定义一个my.log文件,在文件里面写入文字敲下回车,并且保存之后,程序会自动的获取并且打印,可以根据业务需要修改
