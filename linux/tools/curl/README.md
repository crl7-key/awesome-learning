# curl

## 目录
* [简介](#简介)
* [语法](#语法)
* [获取该网址的文本信息](#获取该网址的文本信息)
* [获取该网址的文本信息以及协议头部信息](#获取该网址的文本信息以及协议头部信息)
* [使用代理获取网页文本信息](#使用代理获取网页文本信息)
* [使用post模拟json格式请求接口](#使用post模拟json格式请求接口)
* [仅返回请求头部信息](#仅返回请求头部信息)
* [将链接保存到文件](#将链接保存到文件)
* [跟随链接重定向](#跟随链接重定向)


## 简介
`curl`是常用的命令行工具,用来请求`Web`服务器。它的名字就是客户端（`client`）的`URL`工具的意思。   
它的功能非常强大，命令行参数多达几十种。如果熟练的话，完全可以取代`Postman`这一类的图形界面工具。它支持文件的上传和下载，是综合传输工具,但按传统,习惯称`url`为下载工具。

## 语法
```shell
curl [option] [url]
```
```
常见参数：
-A/--user-agent <string>              设置用户代理发送给服务器
-b/--cookie <name=string/file>        cookie字符串或文件读取位置
-c/--cookie-jar <file>                操作结束后把cookie写入到这个文件中
-C/--continue-at <offset>             断点续转
-D/--dump-header <file>               把header信息写入到该文件中
-e/--referer                          来源网址
-f/--fail                             连接失败时不显示http错误
-o/--output                           把输出写到该文件中
-O/--remote-name                      把输出写到该文件中，保留远程文件的文件名
-r/--range <range>                    检索来自HTTP/1.1或FTP服务器字节范围
-s/--silent                           静音模式。不输出任何东西
-T/--upload-file <fil                 上传文件
-u/--user <user[:password]>           设置服务器的用户和密码
-w/--write-out [format]               什么输出完成后
-x/--proxy <host[:port]>              在给定的端口上使用HTTP代理
-#/--progress-bar                     进度条显示当前的传送状态
```

## 获取该网址的文本信息
```shell
curl url
```
例如:
```shell
curl www.baidu.com
```

## 获取该网址的文本信息以及协议头部信息
```shell
curl -i url
```
例如:
```shell
curl -i www.bilibili.com
```

## 使用代理获取网页文本信息
```
curl -x proxy url
```

## 使用post模拟json格式请求接口
```
curl -X POST --header"Content-Type:application/json" --data ‘{}’ url 
```
> POST :指定请求方式   
> –header: 指定请求头部信息   
> –data : 指定json请求体数据内容   

## 仅返回请求头部信息
```
curl -I url
```
例如:
```
curl -I www.bilibili.com
```

## 将链接保存到文件
```
curl url > test.html
```
可以通过`curl`自带的 `-o/-O`选项将内容保存到文件中。
注意：使用`-O`选项时,必须确保链接末尾包含文件名,否则`curl`无法正确保存文件。如果遇到链接中无文件名的情况，应该使用`-o`选项手动指定文件名,或使用重定向符号。

## 跟随链接重定向
```shell
curl -L url
```
例如：
```
curl -L www.bilibili.com
```

**[⬆ 返回顶部](#目录)**






