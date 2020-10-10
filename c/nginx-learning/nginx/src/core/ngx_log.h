
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#ifndef _NGX_LOG_H_INCLUDED_
#define _NGX_LOG_H_INCLUDED_


#include <ngx_config.h>
#include <ngx_core.h>

// ngx_log_error日志接口level参数的取值范围
// log->log_level中的低4位取值为NGX_LOG_STDERR等  5-12位取值为位图,表示对应模块的日志   另外NGX_LOG_DEBUG_CONNECTION NGX_LOG_DEBUG_ALL对应connect日志和所有日志

// 最高级别日志,日志的内容不会再写入log参数指定的文件,而是会直接将日志输出到标准错误设备，如控制台屏幕 
#define NGX_LOG_STDERR            0

// 大于NGX—LOG ALERT级别,而小于或等于NGX LOG EMERG级别的日志都会输出到log参数指定的文件中  
#define NGX_LOG_EMERG             1

// 大干NGX LOG CRIT级别       
#define NGX_LOG_ALERT             2

// 大干NGX LOG ERR级别   
#define NGX_LOG_CRIT              3

// 大干NGX—LOG WARN级别   
#define NGX_LOG_ERR               4

// 大于NGX LOG NOTICE级别  
#define NGX_LOG_WARN              5     //如果level > NGX_LOG_WARN则不会在屏幕前台打印,见ngx_log_error_core

// 大于NGX__ LOG INFO级别  
#define NGX_LOG_NOTICE            6

// 大于NGX—LOG DEBUG级别
#define NGX_LOG_INFO              7

// 调试级别,最低级别日志
#define NGX_LOG_DEBUG             8


// 在使用ngx_log_debug宏时,level的意义完全不同,它表达的意义不再是级别(已经是DEBUG级别),而是日志类型,因为ngx_log_debug宏记录的日志必须是NGX-LOG—DEBUG调试级别的,这里的level由各子模块定义。

// Nginx核心模块的调试日志
#define NGX_LOG_DEBUG_CORE        0x010

// Nginx在分配内存时使用的调试日志 
#define NGX_LOG_DEBUG_ALLOC       0x020

// Nginx在使用进程锁时使用的调试日志       
#define NGX_LOG_DEBUG_MUTEX       0x040

// Nginx事件模块的调试日志 
#define NGX_LOG_DEBUG_EVENT       0x080

// Nginx http模块的调试日志      
#define NGX_LOG_DEBUG_HTTP        0x100

// Nginx邮件模块的调试日志    
#define NGX_LOG_DEBUG_MAIL        0x200

// 表示与MySQL相关的Nginx模块所使用的调试日志
#define NGX_LOG_DEBUG_STREAM      0x400

/*
 * do not forget to update debug_levels[] in src/core/ngx_log.c
 * after the adding a new debug level
 */

// log->log_level中的低4位取值为NGX_LOG_STDERR等  5-12位取值为位图,表示对应模块的日志   
#define NGX_LOG_DEBUG_FIRST       NGX_LOG_DEBUG_CORE
#define NGX_LOG_DEBUG_LAST        NGX_LOG_DEBUG_STREAM
#define NGX_LOG_DEBUG_CONNECTION  0x80000000    // --with-debug)                    NGX_DEBUG=YES  会打开连接日志 

// 对应connect日志和所有日志
#define NGX_LOG_DEBUG_ALL         0x7ffffff0


typedef u_char *(*ngx_log_handler_pt) (ngx_log_t *log, u_char *buf, size_t len);
typedef void (*ngx_log_writer_pt) (ngx_log_t *log, ngx_uint_t level,
    u_char *buf, size_t len);


struct ngx_log_s {
    // 如果设置的log级别为debug,则会在ngx_log_set_levels把level设置为NGX_LOG_DEBUG_ALL,赋值见ngx_log_set_levels
    
    // 日志级别或者日志类型  默认为NGX_LOG_ERR  如果通过error_log  logs/error.log  info;则为设置的等级  比该级别下的日志可以打印
    ngx_uint_t           log_level;
    
    // 日志文件
    ngx_open_file_t     *file;

    // 连接数,不为O时会输出到日志中
    ngx_atomic_uint_t    connection;

    time_t               disk_full_time;

    // 记录日志时的回调方法。当handler已经实现(不为NULL),并且不是DEBUG调试级别时,才会调用handler钩子方法
    ngx_log_handler_pt   handler; //从连接池获取ngx_connection_t后,c->log->handler = ngx_http_log_error;
    
    //  每个模块都可以自定义data的使用方法。通常,data参数都是在实现了上面的handler回调方法后才使用的。例如:HTTP框架就定义了handler方法,并在data中放入了这个请求的上下文信息,这样每次输出日志时都会把这个请求URI输出到日志的尾部
       
    //指向ngx_http_log_ctx_t,见ngx_http_init_connection
    void                *data;
    
    ngx_log_writer_pt    writer;
    void                *wdata;

    /*
     * we declare "action" as "char *" because the actions are usually
     * the static strings and in the "u_char *" case we have to override
     * their types all the time
     */

    // 当前的动作,只有在实现了handler回调方法后才会使用
    char                *action;

    // ngx_log_insert插入,在ngx_log_error_core找到对应级别的日志配置进行输出,因为可以配置error_log不同级别的日志存储在不同的日志文件中
    ngx_log_t           *next;
};


#define NGX_MAX_ERROR_STR   2048


/*********************************/

#if (NGX_HAVE_C99_VARIADIC_MACROS)

#define NGX_HAVE_VARIADIC_MACROS  1

// 使用ngx_log_error宏记录日志时,如果传人的level级别小于或等于log参数中的日志级别(通常是由nginx.conf配置文件中指定),就会输出日志内容,否则这条日志会被忽略。
#define ngx_log_error(level, log, ...)                                        \
    if ((log)->log_level >= level) ngx_log_error_core(level, log, __VA_ARGS__)

void ngx_log_error_core(ngx_uint_t level, ngx_log_t *log, ngx_err_t err,
    const char *fmt, ...);

#define ngx_log_debug(level, log, ...)                                        \
    if ((log)->log_level & level)                                             \
        ngx_log_error_core(NGX_LOG_DEBUG, log, __VA_ARGS__)

/*********************************/

#elif (NGX_HAVE_GCC_VARIADIC_MACROS)

#define NGX_HAVE_VARIADIC_MACROS  1

#define ngx_log_error(level, log, args...)                                    \
    if ((log)->log_level >= level) ngx_log_error_core(level, log, args)

void ngx_log_error_core(ngx_uint_t level, ngx_log_t *log, ngx_err_t err,
    const char *fmt, ...);

#define ngx_log_debug(level, log, args...)                                    \
    if ((log)->log_level & level)                                             \
        ngx_log_error_core(NGX_LOG_DEBUG, log, args)

/*********************************/

#else /* no variadic macros */

#define NGX_HAVE_VARIADIC_MACROS  0

void ngx_cdecl ngx_log_error(ngx_uint_t level, ngx_log_t *log, ngx_err_t err,
    const char *fmt, ...);
void ngx_log_error_core(ngx_uint_t level, ngx_log_t *log, ngx_err_t err,
    const char *fmt, va_list args);
void ngx_cdecl ngx_log_debug_core(ngx_log_t *log, ngx_err_t err,
    const char *fmt, ...);


#endif /* variadic macros */


/*********************************/

#if (NGX_DEBUG)

#if (NGX_HAVE_VARIADIC_MACROS)
// 注意不能用%V输出,否则会出现段错误
#define ngx_log_debug0(level, log, err, fmt)                                  \
        ngx_log_debug(level, log, err, fmt)

#define ngx_log_debug1(level, log, err, fmt, arg1)                            \
        ngx_log_debug(level, log, err, fmt, arg1)

#define ngx_log_debug2(level, log, err, fmt, arg1, arg2)                      \
        ngx_log_debug(level, log, err, fmt, arg1, arg2)

#define ngx_log_debug3(level, log, err, fmt, arg1, arg2, arg3)                \
        ngx_log_debug(level, log, err, fmt, arg1, arg2, arg3)

#define ngx_log_debug4(level, log, err, fmt, arg1, arg2, arg3, arg4)          \
        ngx_log_debug(level, log, err, fmt, arg1, arg2, arg3, arg4)

#define ngx_log_debug5(level, log, err, fmt, arg1, arg2, arg3, arg4, arg5)    \
        ngx_log_debug(level, log, err, fmt, arg1, arg2, arg3, arg4, arg5)

#define ngx_log_debug6(level, log, err, fmt,                                  \
                       arg1, arg2, arg3, arg4, arg5, arg6)                    \
        ngx_log_debug(level, log, err, fmt,                                   \
                       arg1, arg2, arg3, arg4, arg5, arg6)

#define ngx_log_debug7(level, log, err, fmt,                                  \
                       arg1, arg2, arg3, arg4, arg5, arg6, arg7)              \
        ngx_log_debug(level, log, err, fmt,                                   \
                       arg1, arg2, arg3, arg4, arg5, arg6, arg7)

#define ngx_log_debug8(level, log, err, fmt,                                  \
                       arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8)        \
        ngx_log_debug(level, log, err, fmt,                                   \
                       arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8)


#else /* no variadic macros */

#define ngx_log_debug0(level, log, err, fmt)                                  \
    if ((log)->log_level & level)                                             \
        ngx_log_debug_core(log, err, fmt)

#define ngx_log_debug1(level, log, err, fmt, arg1)                            \
    if ((log)->log_level & level)                                             \
        ngx_log_debug_core(log, err, fmt, arg1)

#define ngx_log_debug2(level, log, err, fmt, arg1, arg2)                      \
    if ((log)->log_level & level)                                             \
        ngx_log_debug_core(log, err, fmt, arg1, arg2)

#define ngx_log_debug3(level, log, err, fmt, arg1, arg2, arg3)                \
    if ((log)->log_level & level)                                             \
        ngx_log_debug_core(log, err, fmt, arg1, arg2, arg3)

#define ngx_log_debug4(level, log, err, fmt, arg1, arg2, arg3, arg4)          \
    if ((log)->log_level & level)                                             \
        ngx_log_debug_core(log, err, fmt, arg1, arg2, arg3, arg4)

#define ngx_log_debug5(level, log, err, fmt, arg1, arg2, arg3, arg4, arg5)    \
    if ((log)->log_level & level)                                             \
        ngx_log_debug_core(log, err, fmt, arg1, arg2, arg3, arg4, arg5)

#define ngx_log_debug6(level, log, err, fmt,                                  \
                       arg1, arg2, arg3, arg4, arg5, arg6)                    \
    if ((log)->log_level & level)                                             \
        ngx_log_debug_core(log, err, fmt, arg1, arg2, arg3, arg4, arg5, arg6)

#define ngx_log_debug7(level, log, err, fmt,                                  \
                       arg1, arg2, arg3, arg4, arg5, arg6, arg7)              \
    if ((log)->log_level & level)                                             \
        ngx_log_debug_core(log, err, fmt,                                     \
                       arg1, arg2, arg3, arg4, arg5, arg6, arg7)

#define ngx_log_debug8(level, log, err, fmt,                                  \
                       arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8)        \
    if ((log)->log_level & level)                                             \
        ngx_log_debug_core(log, err, fmt,                                     \
                       arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8)

#endif

#else /* !NGX_DEBUG */

#define ngx_log_debug0(level, log, err, fmt)
#define ngx_log_debug1(level, log, err, fmt, arg1)
#define ngx_log_debug2(level, log, err, fmt, arg1, arg2)
#define ngx_log_debug3(level, log, err, fmt, arg1, arg2, arg3)
#define ngx_log_debug4(level, log, err, fmt, arg1, arg2, arg3, arg4)
#define ngx_log_debug5(level, log, err, fmt, arg1, arg2, arg3, arg4, arg5)
#define ngx_log_debug6(level, log, err, fmt, arg1, arg2, arg3, arg4, arg5, arg6)
#define ngx_log_debug7(level, log, err, fmt, arg1, arg2, arg3, arg4, arg5,    \
                       arg6, arg7)
#define ngx_log_debug8(level, log, err, fmt, arg1, arg2, arg3, arg4, arg5,    \
                       arg6, arg7, arg8)

#endif

/*********************************/
// 初始化日志
// 默认是NGX_CONF_PREFIX,即/usr/local/nginx
// 如果没有文件名就输出到stderr
// 打开有前缀的日志文件
ngx_log_t *ngx_log_init(u_char *prefix);

// 直接以alert级别记录日志
void ngx_cdecl ngx_log_abort(ngx_err_t err, const char *fmt, ...);

// 在标准错误流输出信息,里面有nginx前缀
void ngx_cdecl ngx_log_stderr(ngx_err_t err, const char *fmt, ...);

// 如果有系统错误码,那么记录(err)
u_char *ngx_log_errno(u_char *buf, u_char *last, ngx_err_t err);

// 打开默认的日志文件,初始化new_log
ngx_int_t ngx_log_open_default(ngx_cycle_t *cycle);

ngx_int_t ngx_log_redirect_stderr(ngx_cycle_t *cycle);

// 在日志链表里找到一个使用文件的日志对象
ngx_log_t *ngx_log_get_file_log(ngx_log_t *head);

// 解析指令,设置日志的级别,插入日志对象链表
char *ngx_log_set_log(ngx_conf_t *cf, ngx_log_t **head);


/*
 * ngx_write_stderr() cannot be implemented as macro, since
 * MSVC does not allow to use #ifdef inside macro parameters.
 *
 * ngx_write_fd() is used instead of ngx_write_console(), since
 * CharToOemBuff() inside ngx_write_console() cannot be used with
 * read only buffer as destination and CharToOemBuff() is not needed
 * for ngx_write_stderr() anyway.
 */

// 写入标准错误
static ngx_inline void
ngx_write_stderr(char *text)
{
    (void) ngx_write_fd(ngx_stderr, text, ngx_strlen(text));
}


// 写入标准输出
static ngx_inline void
ngx_write_stdout(char *text)
{
    (void) ngx_write_fd(ngx_stdout, text, ngx_strlen(text));
}


extern ngx_module_t  ngx_errlog_module;
extern ngx_uint_t    ngx_use_stderr;


#endif /* _NGX_LOG_H_INCLUDED_ */
