# :balloon:nginx-learning :flags:  


## 简介
Nginx源码分析，注解代码，帮助学习Nginx。  

### 源码目录快捷入口
* [src](nginx/src/) - nginx源码目录
* [core](nginx/src/core) - 0%
* [event](nginx/src/event) - 0%
* [http](nginx/src/http) - 0%
* [misc](nginx/src/mail) - 0%
* [os/unix](nginx/src/os/unix) - 0%
* [misc](nginx/src/misc) - 0%
* [stream](nginx/src/stream) - 0%


###### core目录:feet:
* [nginx.c](nginx/src/core/nginx.c)  
* [ngx_conf_file.h](nginx/src/core/ngx_conf_file.h)  
* [ngx_module.h](nginx/src/core/ngx_module.h)  
* [ngx_module.c](nginx/src/core/ngx_module.c)  
* [ngx_connection.h](nginx/src/core/ngx_connection.h)  
* [ngx_connection.c](nginx/src/core/ngx_connection.c)  
* [ngx_thread_pool.h](nginx/src/core/ngx_thread_pool.h)  
* [ngx_thread_pool.c](nginx/src/core/ngx_thread_pool.c)  
* [ngx_palloc.c](nginx/src/core/ngx_palloc.c)  
* [ngx_slab.c](nginx/src/core/ngx_slab.c)  
* [ngx_log.c](nginx/src/core/ngx_log.c)  


###### event目录:balloon:
* [ngx_event.h](/nginx/src/event/ngx_event.h)  
* [ngx_event.c](/nginx/src/event/ngx_event.c)  
* [ngx_event_accept.c](/nginx/src/event/ngx_event_accept.c)  
* [ngx_event_timer.c](/nginx/src/event/ngx_event_timer.c)  
* [ngx_epoll_module.c](/nginx/src/event/modules/ngx_epoll_module.c)  


###### http目录:balloon:
* [ngx_http.h](nginx/src/http/ngx_http.h)  
* [ngx_http.c](nginx/src/http/ngx_http.c)  
* [ngx_http_core_module.h](nginx/src/http/ngx_http_core_module.h)  
* [ngx_http_core_module.c](nginx/src/http/ngx_http_core_module.c)  
* [ngx_http_request.h](nginx/src/http/ngx_http_request.h)  
* [ngx_http_request.c](nginx/src/http/ngx_http_request.c)  
* [ngx_http_request_body.c](nginx/src/http/ngx_http_request_body.c)  
* [ngx_http_header_filter_module.c](nginx/src/http/ngx_http_header_filter_module.c)  
* [ngx_http_write_filter_module.c](nginx/src/http/ngx_http_write_filter_module.c) 


###### http/modules目录:balloon:
* [ngx_http_limit_req_module.c](nginx/src/http/modules/ngx_http_limit_req_module.c) 红黑树和共享内存的使用示例  
* [ngx_http_degradation_module.c](nginx/src/http/modules/ngx_http_degradation_module.c)  
* [ngx_http_upstream_zone_module.c](nginx/src/http/modules/ngx_http_upstream_zone_module.c)  
* [ngx_http_mirror_module.c](nginx/src/http/modules/ngx_http_mirror_module.c)  


###### os/unix目录:balloon:
* [ngx_os.h](nginx/src/os/unix/ngx_os.h)  
* [ngx_process.c](nginx/src/os/unix/ngx_process.c)  
* [ngx_process_cycle.c](nginx/src/os/unix/ngx_process_cycle.c)  
* [ngx_writev_chain.c](nginx/src/os/unix/ngx_writev_chain.c)  

###### stream目录:balloon:
* [ngx_stream.h](nginx/src/stream/ngx_stream.h)  
* [ngx_stream.c](nginx/src/stream/ngx_stream.c)  
* [ngx_stream_core_module.c](nginx/src/stream/ngx_stream_core_module.c)  
* [ngx_stream_handler.c](nginx/src/stream/ngx_stream_handler.c)  

###### misc目录:balloon:    
* [ngx_google_perftools_module.c](nginx/src/misc/ngx_google_perftools_module.c)  

###### 内存管理:balloon:
* [ngx_palloc.c](nginx/src/core/ngx_palloc.c)
* [ngx_slab.c](nginx/src/core/ngx_slab.c)
* [ngx_http_limit_req_module.c](nginx/src/http/modules/ngx_http_limit_req_module.c) 红黑树和共享内存的使用示例
* [ngx_http_degradation_module.c](nginx/src/http/modules/ngx_http_degradation_module.c)
* [ngx_http_upstream_zone_module.c](nginx/src/http/modules/ngx_http_upstream_zone_module.c)

###### 数据结构:balloon:
* [ngx_array.h](nginx/src/core/ngx_array.h)  
* [ngx_list.h](nginx/src/core/ngx_list.h)  
* [ngx_string.h](nginx/src/core/ngx_string.h)  
* [ngx_buf.h](nginx/src/core/ngx_buf.h)  
* [ngx_rbtree.h](nginx/src/core/ngx_rbtree.h)  
* [ngx_http_limit_req_module.c](nginx/src/http/modules/ngx_http_limit_req_module.c) 红黑树和共享内存的使用示例  


###### 进程机制:balloon:
* [nginx.c](nginx/src/core/nginx.c)  
* [ngx_conf_file.h](nginx/src/core/ngx_conf_file.h)  
* [ngx_module.h](nginx/src/core/ngx_module.h)  
* [ngx_module.c](nginx/src/core/ngx_module.c)  
* [ngx_process.c](nginx/src/os/unix/ngx_process.c)  
* [ngx_process_cycle.c](nginx/src/os/unix/ngx_process_cycle.c)  

###### 事件机制:balloon:
* [ngx_connection.h](/nginx/src/core/ngx_connection.h)  
* [ngx_connection.c](/nginx/src/core/ngx_connection.c)  
* [ngx_event.h](/nginx/src/event/ngx_event.h)  
* [ngx_event.c](/nginx/src/event/ngx_event.c)  
* [ngx_event_accept.c](/nginx/src/event/ngx_event_accept.c)  
* [ngx_event_timer.c](/nginx/src/event/ngx_event_timer.c)  
* [ngx_epoll_module.c](/nginx/src/event/modules/ngx_epoll_module.c)  

###### 多线程机制:balloon:
* [ngx_event.h](nginx/src/event/ngx_event.h)  
* [ngx_event.c](nginx/src/event/ngx_event.c)  
* [ngx_thread_pool.h](nginx/src/core/ngx_thread_pool.h)  
* [ngx_thread_pool.c](nginx/src/core/ngx_thread_pool.c)  

###### tcp(stream)处理:balloon:
* [ngx_connection.h](nginx/src/core/ngx_connection.h)  
* [ngx_connection.c](nginx/src/core/ngx_connection.c)  
* [ngx_stream.h](nginx/src/stream/ngx_stream.h)  
* [ngx_stream.c](nginx/src/stream/ngx_stream.c)  
* [ngx_stream_core_module.c](nginx/src/stream/ngx_stream_core_module.c)  
* [ngx_stream_handler.c](nginx/src/stream/ngx_stream_handler.c)  


###### http处理:balloon:
* [ngx_connection.h](nginx/src/core/ngx_connection.h)  
* [ngx_connection.c](nginx/src/core/ngx_connection.c)  
* [ngx_http.h](nginx/src/http/ngx_http.h)  
* [ngx_http.c](nginx/src/http/ngx_http.c)  
* [ngx_http_core_module.h](nginx/src/http/ngx_http_core_module.h)  
* [ngx_http_core_module.c](nginx/src/http/ngx_http_core_module.c)  
* [ngx_http_request.h](nginx/src/http/ngx_http_request.h)  
* [ngx_http_request.c](nginx/src/http/ngx_http_request.c)  
* [ngx_http_request_body.c](nginx/src/http/ngx_http_request_body.c)  
* [ngx_http_header_filter_module.c](nginx/src/http/ngx_http_header_filter_module.c)  
* [ngx_http_write_filter_module.c](nginx/src/http/ngx_http_write_filter_module.c)   




**[⬆ 返回顶部](#源码目录快捷入口)**




