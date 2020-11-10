# Benchmark

```go
func BenchmarkConcatStringByAdd(b* testing.B) {
    // 与性能测试无关的代码
    b.ResetTimer()
    for i := 0; i < b.N; i++ {
        // 测试代码
    }
    b.StopTimer()
    // 与性能测试无关的代码
}
```

# 执行
```sh
go test -bench=. -benchmen
```
- -bench=<相关benchmark测试>
```
go test -bench=benchmark
```
- Windows下使用go test命令时，-bench=.改写为-bench="."

# BDD in Go
项目网站[BDD](https://github.com/smartystreets/goconvey)

安装
```sh
go get -u github.com/smartystreets/goconvey/convey
```

启动WEB UI
> $GOPATH/bin/goconvey
