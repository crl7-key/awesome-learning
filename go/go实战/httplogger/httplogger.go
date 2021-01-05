package httplogger

import (
	"log"
	"net/http"
	"time"
)

type loggedRoundTripper struct {
	rt  http.RoundTripper // 表示执行单个HTTP事务，获取给定请求的响应的能力的接口
	log HttpLogger        //  网络请求日志httplogger
}

func (c *loggedRoundTripper) RoundTrip(request *http.Request) (*http.Response, error) {
	c.log.LogRequest(request)
	startTime := time.Now()
	// log.Println(" 当前时间为 ： ", startTime)
	response, err := c.rt.RoundTrip(request)
	duration := time.Since(startTime)
	c.log.LogResponse(request, response, err, duration)
	return response, err
}

// NewLoggedTransport 使用一个http.RoundTripper并返回一个记录请求和响应的新日志
func NewLoggedTransport(rt http.RoundTripper, log HttpLogger) http.RoundTripper {
	return &loggedRoundTripper{rt: rt, log: log}
}

// HttpLogger httplogger接口
type HttpLogger interface {
	LogRequest(*http.Request)
	LogResponse(*http.Request, *http.Response, error, time.Duration)
}

type DefaultLogger struct {
}

// LogRequest 不执行任何操作，仅响应
func (d DefaultLogger) LogRequest(*http.Request) {
}

// LogResponse 记录路径，主机，状态代码和持续时间
func (d DefaultLogger) LogResponse(req *http.Request, res *http.Response, err error, duration time.Duration) {
	duration /= time.Millisecond
	if err != nil {
		log.Printf("HTTP Request method=%s host=%s path=%s status=error durationMs=%d error=%q", req.Method, req.Host, req.URL.Path, duration, err.Error())
	} else {
		log.Printf("HTTP Request method=%s host=%s path=%s status=%d durationMs=%d", req.Method, req.Host, req.URL.Path, res.StatusCode, duration)
	}
}

// NewLoggedTransport 包装http.DefaultTransport以使用DefaultLogger进行日志记录
var DefaultLoggedTransport = NewLoggedTransport(http.DefaultTransport, DefaultLogger{})
