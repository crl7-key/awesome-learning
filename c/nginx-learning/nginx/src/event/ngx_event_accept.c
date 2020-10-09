
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_event.h>


// 遍历监听端口列表,删除epoll监听连接事件,不接受请求
static ngx_int_t ngx_disable_accept_events(ngx_cycle_t *cycle, ngx_uint_t all);

// 发生了错误,关闭一个连接
static void ngx_close_accepted_connection(ngx_connection_t *c);

/*
 *  建立连接流程:
 *   1) 首先调用accept方法试图建立新连接,如果没有准备好的新连接事件,ngx_event_accept方法会直接返回。
 *   2) 设置负载均衡阈值ngx_accept_disabled,这个阈值是进程允许的总连接数的1/8减去空闲连接数
 *   3) 调用ngx_get_connection方法由连接池中获取一个ngx_connection_t连接对象。
 *   4) 为ngx_connection_t中的pool指针建立内存池。在这个连接释放到空闲连接池时,释放pool内存池。
 *   5) 设置套接字的属性,如设为非阻塞套接字。
 *   6) 将这个新连接对应的读事件添加到epoll等事件驱动模块中,这样，,这个连接上如果接收到用户请求epoll_wait,就会收到这个事件。
 *   7) 调用监听对象ngx_listening_t中的handler回调方法。ngx_listening_t结构俸的handler回调方法就是当新的TCP连接刚刚建立完成时在这里调用的。
 *
 */

// 仅接受tcp连接,ngx_event_process_init里设置接受连接的回调函数为ngx_event_accept,可以接受连接
// 监听端口上收到连接请求时的回调函数,即事件handler,从cycle的连接池里获取连接,关键操作 ls->handler(c); 调用其他模块的业务handler
void
ngx_event_accept(ngx_event_t *ev)
{ // 一个accept事件对应一个ev,如当前一次有4个客户端accept,应该对应4个ev事件,一次来多个accept的处理在下面的do {}while中实现
    socklen_t          socklen;
    ngx_err_t          err;
    ngx_log_t         *log;
    ngx_uint_t         level;
    ngx_socket_t       s;
    
    // 如果是文件异步i/o中的ngx_event_aio_t,则它来自ngx_event_aio_t->ngx_event_t(只有读),如果是网络事件中的event,则为ngx_connection_s中的event(包括读和写)
    ngx_event_t       *rev, *wev;
    
    ngx_sockaddr_t     sa;
    ngx_listening_t   *ls;
    ngx_connection_t  *c, *lc;
    ngx_event_conf_t  *ecf;
#if (NGX_HAVE_ACCEPT4)
    static ngx_uint_t  use_accept4 = 1;
#endif
    // 如果事件已经超时
    if (ev->timedout) {
        
        // 遍历监听端口列表,重新加入epoll连接事件
        if (ngx_enable_accept_events((ngx_cycle_t *) ngx_cycle) != NGX_OK) {
            return;
        }
        // 加入epoll连接事件,重置超时时间,保证监听不超时
        ev->timedout = 0;
    }

    // 得到event core模块的配置,检查是否接受多个连接
    ecf = ngx_event_get_conf(ngx_cycle->conf_ctx, ngx_event_core_module);

    // epoll是否允许尽可能接受多个请求
    if (!(ngx_event_flags & NGX_USE_KQUEUE_EVENT)) {
        // ev->available仅使用1个bit的内存空间
        ev->available = ecf->multi_accept;
    }

    // 事件的连接对象
    lc = ev->data;
    
    // 事件对应的监听端口对象,这里是一个关键: 连接->事件->监听端口  定了要进入stream还是http子系统
    ls = lc->listening;
    
    // 此时还没有数据可读
    ev->ready = 0;

    ngx_log_debug2(NGX_LOG_DEBUG_EVENT, ev->log, 0,
                   "accept on %V, ready: %d", &ls->addr_text, ev->available);

    do { // 如果是一次读取一个accept事件的话,循环体只执行一次. 如果是一次性可以读取所有的accept事件,则这个循环体执行次数为accept事件数
        socklen = sizeof(ngx_sockaddr_t);

        
        // 调用accept接受连接,返回socket对象,accept4是linux的扩展功能,可以直接把连接的socket设置为非阻塞
#if (NGX_HAVE_ACCEPT4)
        if (use_accept4) {
            s = accept4(lc->fd, &sa.sockaddr, &socklen, SOCK_NONBLOCK);
        } else {
            s = accept(lc->fd, &sa.sockaddr, &socklen);
        }
#else
        s = accept(lc->fd, &sa.sockaddr, &socklen);
#endif

        // 接受连接出错
        if (s == (ngx_socket_t) -1) {
            err = ngx_socket_errno;

            // EAGAIN,此时已经没有新的连接,用于multi_accept
            if (err == NGX_EAGAIN) {
                ngx_log_debug0(NGX_LOG_DEBUG_EVENT, ev->log, err,
                               "accept() not ready");
                return;
            }

            level = NGX_LOG_ALERT;

            // 对方关闭连接,重传
            if (err == NGX_ECONNABORTED) {
                level = NGX_LOG_ERR;

             // 系统的文件句柄数用完
            } else if (err == NGX_EMFILE || err == NGX_ENFILE) {
                level = NGX_LOG_CRIT;
            }

#if (NGX_HAVE_ACCEPT4)
            ngx_log_error(level, ev->log, err,
                          use_accept4 ? "accept4() failed" : "accept() failed");

            if (use_accept4 && err == NGX_ENOSYS) {
                use_accept4 = 0;
                ngx_inherited_nonblocking = 0;
                continue;
            }
#else
            ngx_log_error(level, ev->log, err, "accept() failed");
#endif

            if (err == NGX_ECONNABORTED) {
                if (ngx_event_flags & NGX_USE_KQUEUE_EVENT) {
                    ev->available--;
                }

                if (ev->available) {
                    continue;
                }
            }

             // 系统的文件句柄数用完
            if (err == NGX_EMFILE || err == NGX_ENFILE) {
                
                // 遍历监听端口列表,删除epoll监听连接事件,不接受请求
                if (ngx_disable_accept_events((ngx_cycle_t *) ngx_cycle, 1)
                    != NGX_OK)
                {
                    return;
                }

                // 解锁负载均衡,允许其他进程接受请求
                if (ngx_use_accept_mutex) {
                    if (ngx_accept_mutex_held) {
                        ngx_shmtx_unlock(&ngx_accept_mutex);
                        ngx_accept_mutex_held = 0;
                    }

                    // 未持有锁,暂时不接受请求
                    ngx_accept_disabled = 1;

                } else {
                    // 不使用负载均衡,等待一下,再次尝试接受请求
                    ngx_add_timer(ev, ecf->accept_mutex_delay);
                }
            }

            return;
        }// 接受连接出错

#if (NGX_STAT_STUB)
        (void) ngx_atomic_fetch_add(ngx_stat_accepted, 1);
#endif
    
        // 此时accept返回了一个socket描述符s
        
        // 设置负载均衡阈值ngx_accept_disabled = 进程允许的总连接数的1/8 - 空闲连接数 , 也就是说空闲连接数小于总数的1/8,那么就暂时停止接受连接
        ngx_accept_disabled = ngx_cycle->connection_n / 8
                              - ngx_cycle->free_connection_n;

        // 从全局变量ngx_cycle里获取空闲链接,即free_connections链表
        c = ngx_get_connection(s, ev->log);

        // 如果没有空闲连接,那么关闭socket,无法处理请求
        if (c == NULL) {
            if (ngx_close_socket(s) == -1) {
                ngx_log_error(NGX_LOG_ALERT, ev->log, ngx_socket_errno,
                              ngx_close_socket_n " failed");
            }

            return;
        }

        // 1.10连接对象里新的字段,表示连接类型是tcp
        c->type = SOCK_STREAM;

#if (NGX_STAT_STUB)
        (void) ngx_atomic_fetch_add(ngx_stat_active, 1);
#endif

        // 创建连接使用的内存池
        // stream模块设置连接的内存池是256bytes,不可配置
        // http模块可以在ngx_http_core_srv_conf_t里配置
        c->pool = ngx_create_pool(ls->pool_size, ev->log);
        if (c->pool == NULL) { // 创建失败,关闭连接
            ngx_close_accepted_connection(c);
            return;
        }
        
        // 拷贝客户端sockaddr大小
        if (socklen > (socklen_t) sizeof(ngx_sockaddr_t)) {
            socklen = sizeof(ngx_sockaddr_t);
        }

        // 拷贝客户端sockaddr
        c->sockaddr = ngx_palloc(c->pool, socklen);
        if (c->sockaddr == NULL) {
            ngx_close_accepted_connection(c);
            return;
        }

        ngx_memcpy(c->sockaddr, &sa, socklen);

        // 连接使用一个新的日志对象
        log = ngx_palloc(c->pool, sizeof(ngx_log_t));
        if (log == NULL) {
            ngx_close_accepted_connection(c);
            return;
        }

        /* set a blocking mode for iocp and non-blocking mode for others */

        // 设置socket为非阻塞
        // ngx_inherited_nonblocking => os/unix/ngx_posix_init.c
        // 如果linux支持accept4,那么ngx_inherited_nonblocking = true
        if (ngx_inherited_nonblocking) {
            
            // NGX_USE_IOCP_EVENT是win32的标志,这段代码在linux里不会执行,也就是说无动作,因为accept4已经设置了socket非阻塞
            if (ngx_event_flags & NGX_USE_IOCP_EVENT) {
                if (ngx_blocking(s) == -1) {
                    ngx_log_error(NGX_LOG_ALERT, ev->log, ngx_socket_errno,
                                  ngx_blocking_n " failed");
                    ngx_close_accepted_connection(c);
                    return;
                }
            }

        } else {// 如果linux不支持accept4,需要设置为非阻塞
            if (!(ngx_event_flags & NGX_USE_IOCP_EVENT)) {
                if (ngx_nonblocking(s) == -1) {
                    ngx_log_error(NGX_LOG_ALERT, ev->log, ngx_socket_errno,
                                  ngx_nonblocking_n " failed");
                    ngx_close_accepted_connection(c);
                    return;
                }
            }
        }

        // 从监听端口拷贝
        *log = ls->log;

        // 连接的收发数据函数
        // #define ngx_recv             ngx_io.recv
        // #define ngx_recv_chain       ngx_io.recv_chain
        // ngx_posix_init.c里初始化为linux的底层接口
        c->recv = ngx_recv;
        c->send = ngx_send;
        c->recv_chain = ngx_recv_chain;
        c->send_chain = ngx_send_chain;

        c->log = log;
        c->pool->log = log;

        // 设置其他的成员
        c->socklen = socklen;
        c->listening = ls;
        c->local_sockaddr = ls->sockaddr;
        c->local_socklen = ls->socklen;

#if (NGX_HAVE_UNIX_DOMAIN)
        if (c->sockaddr->sa_family == AF_UNIX) {
            c->tcp_nopush = NGX_TCP_NOPUSH_DISABLED;
            c->tcp_nodelay = NGX_TCP_NODELAY_DISABLED;
#if (NGX_SOLARIS)
            /* Solaris's sendfilev() supports AF_NCA, AF_INET, and AF_INET6 */
            c->sendfile = 0;
#endif
        }
#endif

        // 连接相关的读写事件
        rev = c->read;
        wev = c->write;

        // 建立连接后是可写的
        wev->ready = 1;

         // linux里这段代码不执行
        if (ngx_event_flags & NGX_USE_IOCP_EVENT) {
            rev->ready = 1;
        }

         // 如果listen使用了deferred,那么建立连接时就已经有数据可读了,否则需要自己再加读事件,当有数据来时才能读取
        if (ev->deferred_accept) {
            rev->ready = 1;
#if (NGX_HAVE_KQUEUE || NGX_HAVE_EPOLLRDHUP)
            rev->available = 1;
#endif
        }

        rev->log = log;
        wev->log = log;

        /*
         * TODO: MT: - ngx_atomic_fetch_add()
         *             or protection by critical section or light mutex
         *
         * TODO: MP: - allocated in a shared memory
         *           - ngx_atomic_fetch_add()
         *             or protection by critical section or light mutex
         */

        // 连接计数器增加
        c->number = ngx_atomic_fetch_add(ngx_connection_counter, 1);

#if (NGX_STAT_STUB)
        (void) ngx_atomic_fetch_add(ngx_stat_handled, 1);
#endif

        if (ls->addr_ntop) {
            c->addr_text.data = ngx_pnalloc(c->pool, ls->addr_text_max_len);
            if (c->addr_text.data == NULL) {
                ngx_close_accepted_connection(c);
                return;
            }

            c->addr_text.len = ngx_sock_ntop(c->sockaddr, c->socklen,
                                             c->addr_text.data,
                                             ls->addr_text_max_len, 0);
            if (c->addr_text.len == 0) {
                ngx_close_accepted_connection(c);
                return;
            }
        }

#if (NGX_DEBUG)
        {
        ngx_str_t  addr;
        u_char     text[NGX_SOCKADDR_STRLEN];

        ngx_debug_accepted_connection(ecf, c);

        if (log->log_level & NGX_LOG_DEBUG_EVENT) {
            addr.data = text;
            addr.len = ngx_sock_ntop(c->sockaddr, c->socklen, text,
                                     NGX_SOCKADDR_STRLEN, 1);

            ngx_log_debug3(NGX_LOG_DEBUG_EVENT, log, 0,
                           "*%uA accept: %V fd:%d", c->number, &addr, s);
        }

        }
#endif

        // 如果事件机制不是epoll,连接的读写事件都加入监控,即有读写都会由select/poll/kqueue等收集事件并处理
        if (ngx_add_conn && (ngx_event_flags & NGX_USE_EPOLL_EVENT) == 0) {
            if (ngx_add_conn(c) == NGX_ERROR) {
                ngx_close_accepted_connection(c);
                return;
            }
        }

        // 在linux上通常都使用epoll,所以上面的if代码不会执行,需要在后续的处理流程中自己控制读写事件的监控事件
        
        
        log->data = NULL;
        log->handler = NULL;

        // 接受连接,收到请求的回调函数
        // 在http模块里是http.c:ngx_http_init_connection
        // stream模块里是ngx_stream_init_connection
        ls->handler(c);

        // epoll不处理
        if (ngx_event_flags & NGX_USE_KQUEUE_EVENT) {
            ev->available--;
        }

    // 如果ev->available = ecf->multi_accept;
    // epoll尽可能接受多个请求,直至accept出错EAGAIN,即无新连接请求,否则epoll只接受一个请求后即退出循环
    } while (ev->available);
}

// 尝试获取负载均衡锁,监听端口,如未获取则不监听端口,锁标志ngx_accept_mutex_held
// 内部调用ngx_enable_accept_events/ngx_disable_accept_events,在ngx_event.c:ngx_process_events_and_timers里被调用
ngx_int_t
ngx_trylock_accept_mutex(ngx_cycle_t *cycle)
{
    
    // 尝试锁定共享内存锁,非阻塞,会立即返回
    if (ngx_shmtx_trylock(&ngx_accept_mutex)) {

        ngx_log_debug0(NGX_LOG_DEBUG_EVENT, cycle->log, 0,
                       "accept mutex locked");

        // 锁成功

        // 之前已经持有了锁,那么就直接返回,继续监听端口, ngx_accept_events在epoll里不使用
        // 有ngx_accept_mutex_held标记,表示该进程已经把accept事件添加到epoll事件集中了,不用重复执行后面的ngx_enable_accept_events,该函数是有系统调用过程,影响性能
        if (ngx_accept_mutex_held && ngx_accept_events == 0) {
            return NGX_OK;
        }

        // 之前没有持有锁,需要注册epoll事件监听端口
        //  到达这里,说明重新获得锁成功,因此需要打开被关闭的listening句柄,调用ngx_enable_accept_events函数,将监听端口注册到当前worker进程的epoll当中去
        
        // 遍历监听端口列表,加入epoll连接事件,开始接受请求
        if (ngx_enable_accept_events(cycle) == NGX_ERROR) {
            
            // 如果监听失败就需要立即解锁,函数结束
            ngx_shmtx_unlock(&ngx_accept_mutex);
            return NGX_ERROR;
        }

        // 已经成功将监听事件加入epoll

        // 设置已经获得锁的标志
        ngx_accept_events = 0;
        
        // 表示当前获取了锁   
        ngx_accept_mutex_held = 1;

        return NGX_OK;
    }

    // try失败,未获得锁,极小的消耗
    
    ngx_log_debug1(NGX_LOG_DEBUG_EVENT, cycle->log, 0,
                   "accept mutex lock failed: %ui", ngx_accept_mutex_held);

    // 未获得锁,但之前持有锁,也就是说之前在监听端口,是以前曾经获取过,但是这次却获取失败了,那么需要将监听端口从当前的worker进程的epoll当中移除,调用的是ngx_disable_accept_events函数   
    if (ngx_accept_mutex_held) {
        
        // 遍历监听端口列表,删除epoll监听连接事件,不接受请求
        if (ngx_disable_accept_events(cycle, 0) == NGX_ERROR) {
            return NGX_ERROR;
        }

        // 设置未获得锁的标志
        ngx_accept_mutex_held = 0;
    }

    return NGX_OK;
}

// 遍历监听端口列表,加入epoll连接事件,开始接受请求
ngx_int_t
ngx_enable_accept_events(ngx_cycle_t *cycle)
{
    ngx_uint_t         i;
    ngx_listening_t   *ls;
    ngx_connection_t  *c;

    // 遍历监听端口列表
    ls = cycle->listening.elts;
    /*  本进程ngx_enable_accept_events把所有listen加入本进程epoll中后,本进程获取到ngx_accept_mutex锁后,在执行accept事件的
        过程中如果如果其他进程也开始ngx_trylock_accept_mutex,如果之前已经获取到锁,并把所有的listen添加到了epoll中,这时会因为没法获取到
        accept锁,而把之前加入到本进程,但没有accept过的时间全部清除。和ngx_disable_accept_events配合使用,最终只有一个进程能accept到同一个客户端连接 */
    for (i = 0; i < cycle->listening.nelts; i++) {

        c = ls[i].connection;

        // 如果连接已经监听(读事件激活)那么就跳过
        if (c == NULL || c->read->active) {
            continue;
        }

        // #define ngx_add_event        ngx_event_actions.add
        // 加入读事件,即接受连接事件
        if (ngx_add_event(c->read, NGX_READ_EVENT, 0) == NGX_ERROR) {
            return NGX_ERROR;
        }
    }

    return NGX_OK;
}


// 遍历监听端口列表,删除epoll监听连接事件,不接受请求
static ngx_int_t
ngx_disable_accept_events(ngx_cycle_t *cycle, ngx_uint_t all)
{
    ngx_uint_t         i;
    ngx_listening_t   *ls;
    ngx_connection_t  *c;

     // 遍历监听端口列表
    ls = cycle->listening.elts;
    for (i = 0; i < cycle->listening.nelts; i++) {

        c = ls[i].connection;

         // 如果连接已经监听(读事件激活)那么就跳过
        if (c == NULL || !c->read->active) {
            continue;
        }

#if (NGX_HAVE_REUSEPORT)

        /*
         * do not disable accept on worker's own sockets
         * when disabling accept events due to accept mutex
         */

        if (ls[i].reuseport && !all) {
            continue;
        }

#endif

        // 删除读事件，即不接受连接事件
        // NGX_DISABLE_EVENT暂时无用
        if (ngx_del_event(c->read, NGX_READ_EVENT, NGX_DISABLE_EVENT)
            == NGX_ERROR)
        {
            return NGX_ERROR;
        }
    }

    return NGX_OK;
}


// 发生了错误,关闭一个连接
static void
ngx_close_accepted_connection(ngx_connection_t *c)
{
    ngx_socket_t  fd;

    // 释放连接,加入空闲链表  in core/ngx_connection.c
    ngx_free_connection(c);

    // 连接的描述符置为无效
    fd = c->fd;
    c->fd = (ngx_socket_t) -1;

    // 关闭socket
    if (ngx_close_socket(fd) == -1) {
        ngx_log_error(NGX_LOG_ALERT, c->log, ngx_socket_errno,
                      ngx_close_socket_n " failed");
    }

    // 释放连接相关的所有内存
    if (c->pool) {
        ngx_destroy_pool(c->pool);
    }

#if (NGX_STAT_STUB)
    (void) ngx_atomic_fetch_add(ngx_stat_active, -1);
#endif
}


u_char *
ngx_accept_log_error(ngx_log_t *log, u_char *buf, size_t len)
{
    return ngx_snprintf(buf, len, " while accepting new connection on %V",
                        log->data);
}


#if (NGX_DEBUG)

void
ngx_debug_accepted_connection(ngx_event_conf_t *ecf, ngx_connection_t *c)
{
    struct sockaddr_in   *sin;
    ngx_cidr_t           *cidr;
    ngx_uint_t            i;
#if (NGX_HAVE_INET6)
    struct sockaddr_in6  *sin6;
    ngx_uint_t            n;
#endif

    cidr = ecf->debug_connection.elts;
    for (i = 0; i < ecf->debug_connection.nelts; i++) {
        if (cidr[i].family != (ngx_uint_t) c->sockaddr->sa_family) {
            goto next;
        }

        switch (cidr[i].family) {

#if (NGX_HAVE_INET6)
        case AF_INET6:
            sin6 = (struct sockaddr_in6 *) c->sockaddr;
            for (n = 0; n < 16; n++) {
                if ((sin6->sin6_addr.s6_addr[n]
                    & cidr[i].u.in6.mask.s6_addr[n])
                    != cidr[i].u.in6.addr.s6_addr[n])
                {
                    goto next;
                }
            }
            break;
#endif

#if (NGX_HAVE_UNIX_DOMAIN)
        case AF_UNIX:
            break;
#endif

        default: /* AF_INET */
            sin = (struct sockaddr_in *) c->sockaddr;
            if ((sin->sin_addr.s_addr & cidr[i].u.in.mask)
                != cidr[i].u.in.addr)
            {
                goto next;
            }
            break;
        }

        c->log->log_level = NGX_LOG_DEBUG_CONNECTION|NGX_LOG_DEBUG_ALL;
        break;

    next:
        continue;
    }
}

#endif
