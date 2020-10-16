package main

import (
    "io"
    "io/ioutil"
    "log"
    "net/http"

    "github.com/julienschmidt/httprouter"
)

  // 文件上传最大大小
const (
    MAX_UPLOAD_SIZE = 1024 * 1024 * 20 //50MB
)

func main() {
   // 注册路由
    r := RegisterHandlers()
  
    // 监听端口8080
    http.ListenAndServe(":8080", r)
}

// 注册路由
func RegisterHandlers() *httprouter.Router {
    router := httprouter.New()

    router.POST("/upload", uploadHandler)

    return router
}

// 上传句柄
func uploadHandler(w http.ResponseWriter, r *http.Request, p httprouter.Params) {
    
    r.Body = http.MaxBytesReader(w, r.Body, MAX_UPLOAD_SIZE)
    if err := r.ParseMultipartForm(MAX_UPLOAD_SIZE); err != nil {
        log.Printf("File is too big")
        return
    }
    
    file, headers, err := r.FormFile("file")
    if err != nil {
        log.Printf("Error when try to get file: %v", err)
        return
    }
    
    //获取上传文件的类型
    if headers.Header.Get("Content-Type") != "image/png" {
        log.Printf("只允许上传png图片")
        return
    }
    
    data, err := ioutil.ReadAll(file)
    if err != nil {
        log.Printf("Read file error: %v", err)
        return
    }
    // 获取文件名
    fn := headers.Filename
    // 写入文件
    err = ioutil.WriteFile("./video/"+fn, data, 0666)
    if err != nil {
        log.Printf("Write file error: %v", err)
        return
    }
    // 响应
    w.WriteHeader(http.StatusCreated)
    io.WriteString(w, "Uploaded successfully")
    
}
