# Go实战--golang中执行cron job定时任务(robfig/cron和jasonlvhit/gocron)

## Linux下crontab
`crontab`命令常见于`Unix`和类`Unix`的操作系统之中，用于设置周期性被执行的指令。 该命令从标准输入设备读取指令，并将其存放于“`crontab`”文件中，以供之后读取和执行。 该词来源于希腊语`chronos`（`χρόνος`），原意是时间。

通常，`crontab`储存的指令被守护进程激活，`crond`常常在后台运行，每一分钟检查是否有预定的作业需要执行。这类作业一般称为`cron jobs`。

`crontab`文件包含送交`cron`守护进程的一系列作业和指令。每个用户可以拥有自己的`crontab`文件；同时，操作系统保存一个针对整个系统的`crontab`文件，该文件通常存放于`/etc`或者`/etc`之下的子目录中，而这个文件只能由系统管理员来修改。

`crontab`文件的每一行均遵守特定的格式，由空格或`tab`分隔为数个领域，每个领域可以放置单一或多个数值。

例如：配置文件`/etc/crontab`如下：
```sh
#  m  h  dow mon  user  command
17   *       * * *         root    cd / && run-parts --report /etc/cron.hourly
每个小时的第17分钟去执行
25   6       * * *        root    test -x /usr/sbin/anacron || ( cd / && run-parts --report /etc/cron.daily )
每天的6点25分去执行
47   6       * * 7       root    test -x /usr/sbin/anacron || ( cd / && run-parts --report /etc/cron.weekly )
每周的星期天6点47分去执行
52   6       1 * *       root    test -x /usr/sbin/anacron || ( cd / && run-parts --report /etc/cron.monthly )
每月的1号的6点52分区执行
```

## 命令
安装`crontab`：
```sh
yum install crontabs
```
启动：
```sh
service crond start
```

关闭：
```sh
service crond stop
```

重启：
```sh
service crond restart
```

重载：
```sh
service crond reload
```

查看状态：
```sh
service crond status
```
编辑任务：
```sh
crontab -e
```

查看任务：
```sh
crontab -l
```

删除：
```sh
crontab -r
```

## 格式
```
分 时 日 月 星期 要运行的命令
```
## 操作符号
在一个区域里填写多个数值的方法：
- 逗号（’`,`’）分开的值，例如：“`1`,`3`,`4`,`7`,`8`”
- 连词符（’-‘）指定值的范围，例如：“`1-6`”，意思等同于“`1`,`2`,`3`,`4`,`5`,`6`”
- 星号（’`*`’）代表任何可能的值。例如，在“小时域”里的星号等于是“每一个小时”，等等
- 某些`cron`程序的扩展版本也支持斜线（’`/`’）操作符，用于表示跳过某些给定的数。例如，“`*/3`”在小时域中等于“`0`,`3`,`6`,`9`,`12`,`15`,`18`,`21`”等被3整除的数；

## 实例
每分钟执行一次命令：
```sh
* * * * * yourCommand
```
每小时的第`2`和第`10`分钟执行：
```sh
2,10 * * * * yourCommand
```
每天上午`9`点到`12`点的第`2`和第`10`分钟执行：
```sh
2,10 9-12 * * * yourCommand
```
每隔两天的上午`9`点到`12`点的第`2`和第`10`分钟执行：
```sh
2,10 9-12 */2 * * yourCommand
```
每周一上午`9`点到`12`点的第`2`和第`10`分钟执行：
```sh
2,10 9-12 * * 1 yourCommand
```

在`golang中`也有非常好的`cron`库   
## [robfig/cron](https://github.com/robfig/cron)

安装：
```sh
go get -u github.com/robfig/cron
```
应用：  

每分钟执行一次：
```golang
package main

import (
    "log"

    "github.com/robfig/cron"
)

func main() {
    i := 0
    c := cron.New()
    spec := "0 */1 * * * *"
    c.AddFunc(spec, func() {
        i++
        log.Println("execute per second", i)
    })
    c.Start()
    select {}
}
```
其中注意`select`的用法：  

`golang`的`select`的功能和`select`, `poll`, `epoll`相似， 就是监听`IO`操作，当`IO`操作发生时，触发相应的动作。

**每天上午`9`点到`12`点的第`2`和第`10`分钟执行**：
```golang
package main

import (
    "fmt"

    "github.com/robfig/cron"
)

func main() {
    spec := "2,10 9-12 * * *"           // 每天上午9点到12点的第2和第10分钟执行
    c := cron.New()
    c.AddFunc(spec, myFunc)
    c.Start()
    select {}
}

func myFunc() {
    fmt.Println("execute")
}
```

## [jasonlvhit/gocron](https://github.com/jasonlvhit/gocron)

安装：
```sh
go get -u github.com/jasonlvhit/gocron
```

每隔`1`秒执行一个任务，每隔`4`秒执行另一个任务：
```golang
package main

import (
    "fmt"
    "time"

    "github.com/jasonlvhit/gocron"
)

func task() {
    fmt.Println("I am runnning task.", time.Now())
}

func task2() {
	fmt.Println("I am runnning task2.", time.Now())
}

func main() {
    g := gocron.NewScheduler()
	g.Every(1).Seconds().Do(task)
	g.Every(4).Seconds().Do(task2)

	gc := g.Start() // keep the channel
	go test(g, gc)  // wait
	<-gc            // it will happens if the channel is closed
}

func test(g *gocron.Scheduler, gc chan bool) {
	time.Sleep(8 * time.Second)
	g.Remove(task) //remove task
	time.Sleep(8 * time.Second)
	g.Clear()
	fmt.Println("All task removed")
	close(gc) // close the channel
}

```