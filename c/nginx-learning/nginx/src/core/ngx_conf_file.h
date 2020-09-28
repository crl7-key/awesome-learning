
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#ifndef _NGX_CONF_FILE_H_INCLUDED_
#define _NGX_CONF_FILE_H_INCLUDED_


#include <ngx_config.h>
#include <ngx_core.h>


/*
 *        AAAA  number of arguments
 *      FF      command flags
 *    TT        command type, i.e. HTTP "location" or "server" command
 */
// nginx指令可以接受的参数数量
#define NGX_CONF_NOARGS      0x00000001
#define NGX_CONF_TAKE1       0x00000002
#define NGX_CONF_TAKE2       0x00000004
#define NGX_CONF_TAKE3       0x00000008
#define NGX_CONF_TAKE4       0x00000010
#define NGX_CONF_TAKE5       0x00000020
#define NGX_CONF_TAKE6       0x00000040
#define NGX_CONF_TAKE7       0x00000080
// 最多只能接收8个参数
#define NGX_CONF_MAX_ARGS    8
// 组合之前的参数
#define NGX_CONF_TAKE12      (NGX_CONF_TAKE1|NGX_CONF_TAKE2)
#define NGX_CONF_TAKE13      (NGX_CONF_TAKE1|NGX_CONF_TAKE3)

#define NGX_CONF_TAKE23      (NGX_CONF_TAKE2|NGX_CONF_TAKE3)

#define NGX_CONF_TAKE123     (NGX_CONF_TAKE1|NGX_CONF_TAKE2|NGX_CONF_TAKE3)
#define NGX_CONF_TAKE1234    (NGX_CONF_TAKE1|NGX_CONF_TAKE2|NGX_CONF_TAKE3   \
                              |NGX_CONF_TAKE4)

// 特殊的指令属性
#define NGX_CONF_ARGS_NUMBER 0x000000ff
#define NGX_CONF_BLOCK       0x00000100     // 指令是配置块,即{...}
#define NGX_CONF_FLAG        0x00000200     // 指令接受on/off,即转化为ngx_flag_t
#define NGX_CONF_ANY         0x00000400 
#define NGX_CONF_1MORE       0x00000800
#define NGX_CONF_2MORE       0x00001000

#define NGX_DIRECT_CONF      0x00010000

#define NGX_MAIN_CONF        0x01000000     // 指令出现在配置文件的最外层
#define NGX_ANY_CONF         0xFF000000     // 指令可以在任意位置出现



#define NGX_CONF_UNSET       -1
#define NGX_CONF_UNSET_UINT  (ngx_uint_t) -1
#define NGX_CONF_UNSET_PTR   (void *) -1
#define NGX_CONF_UNSET_SIZE  (size_t) -1
#define NGX_CONF_UNSET_MSEC  (ngx_msec_t) -1


#define NGX_CONF_OK          NULL
#define NGX_CONF_ERROR       (void *) -1
// 配置解析时的标质量,表示解析的状态
#define NGX_CONF_BLOCK_START 1
#define NGX_CONF_BLOCK_DONE  2
#define NGX_CONF_FILE_DONE   3
// 最基本的两个模块的标志,core模块和conf模块
#define NGX_CORE_MODULE      0x45524F43  /* "CORE" */
#define NGX_CONF_MODULE      0x464E4F43  /* "CONF" */


#define NGX_MAX_CONF_ERRSTR  1024

// 指令结构体，用于定义nginx指令 ngx_commadn_t(ngx_core.h)
struct ngx_command_s {
    ngx_str_t             name; // 指令的名字
    ngx_uint_t            type; // 指令的类型,是NGX_CONF_XXX的组合,决定指令出现的位置、参数数量、类型等 NGX_HTTP_MAIN_CONF/NGX_HTTP_SRV_CONF/NGX_HTTP_LOC_CONF
    // 指令解析函数，是函数指针，预设有ngx_conf_set_flag_slot等，见本文件
    // cf : 解析的环境结构体,重要的是cf->args，是指令字符串数组
    // cmd：该指令的结构体
    // conf当前的配置结构体，需转型后才能使用
    char               *(*set)(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
  
    ngx_uint_t            conf;   // 主要给http/stream模块使用，决定存储在main/srv/loc的哪个层次 NGX_HTTP_MAIN_CONF_OFFSET/NGX_HTTP_SRV_CONF_OFFSET/NGX_HTTP_LOC_CONF_OFFSET/NGX_STREAM_MAIN_CONF_OFFSET  其他类型的模块不使用，直接为0
      
    ngx_uint_t            offset; // 变量在conf结构体里的偏移量，可用offsetof得到,主要用于nginx内置的命令解析函数，自己写命令解析函数可以置为0
    void                 *post;   // 解析后处理的数据
};
// 空指令，用于在指令数组的最后当做哨兵，结束数组，避免指定长度，类似NULL的作用
#define ngx_null_command  { ngx_null_string, 0, NULL, 0, 0, NULL }

// typedef struct ngx_open_file_s       ngx_open_file_t; 主要用来管理日志文件,存储在cycle->open_files列表里
struct ngx_open_file_s {
    ngx_fd_t              fd;
    ngx_str_t             name;

    void                (*flush)(ngx_open_file_t *file, ngx_log_t *log);
    void                 *data;
};


typedef struct {
    ngx_file_t            file;
    ngx_buf_t            *buffer;
    ngx_buf_t            *dump;
    ngx_uint_t            line;
} ngx_conf_file_t;


typedef struct {
    ngx_str_t             name;
    ngx_buf_t            *buffer;
} ngx_conf_dump_t;

// 解析配置的函数指针
typedef char *(*ngx_conf_handler_pt)(ngx_conf_t *cf,
    ngx_command_t *dummy, void *conf);

// 配置解析的环境结构体
struct ngx_conf_s {
    char                 *name;
   
    ngx_array_t          *args;  // 保存解析到的指令字符串,0是指令名，其他的是参数

    ngx_cycle_t          *cycle; // 当前配置的cycle结构体，用于添加监听端口 
    ngx_pool_t           *pool;  // 内存池，可以从这里分配内存
    ngx_pool_t           *temp_pool; // 临时内存池 
    ngx_conf_file_t      *conf_file;
    ngx_log_t            *log;  // 配置解析时使用的log对象

    void                 *ctx;// 重要参数，解析时的上下文,解析开始时是cycle->conf_ctx，即普通数组,在stream{}里是ngx_stream_conf_ctx_t,在events{}里是个存储void*的数组，即void**,在http{}里是ngx_http_conf_ctx_t
    ngx_uint_t            module_type;// 解析配置文件当前的模块类型，解析时检查
    ngx_uint_t            cmd_type; // 解析配置文件当前的命令类型，解析时检查

    ngx_conf_handler_pt   handler;// 解析配置的函数指针，可以忽略指令，直接处理配置文件内容types {...}就使用了这个实现
    void                 *handler_conf;
};

// 可以在解析完成后再执行一些操作
typedef char *(*ngx_conf_post_handler_pt) (ngx_conf_t *cf,
    void *data, void *conf);
// 用于解析指令的额外数据，存储函数指针
typedef struct {
    ngx_conf_post_handler_pt  post_handler;
} ngx_conf_post_t;


typedef struct {
    ngx_conf_post_handler_pt  post_handler;
    char                     *old_name;
    char                     *new_name;
} ngx_conf_deprecated_t;


typedef struct {
    ngx_conf_post_handler_pt  post_handler;
    ngx_int_t                 low;
    ngx_int_t                 high;
} ngx_conf_num_bounds_t;


typedef struct {
    ngx_str_t                 name;
    ngx_uint_t                value;
} ngx_conf_enum_t;


#define NGX_CONF_BITMASK_SET  1

typedef struct {
    ngx_str_t                 name;
    ngx_uint_t                mask;
} ngx_conf_bitmask_t;



char * ngx_conf_deprecated(ngx_conf_t *cf, void *post, void *data);
char *ngx_conf_check_num_bounds(ngx_conf_t *cf, void *post, void *data);


#define ngx_get_conf(conf_ctx, module)  conf_ctx[module.index]


// 简单的初始化函数宏，针对各种类型操作
#define ngx_conf_init_value(conf, default)                                   \
    if (conf == NGX_CONF_UNSET) {                                            \
        conf = default;                                                      \
    }

#define ngx_conf_init_ptr_value(conf, default)                               \
    if (conf == NGX_CONF_UNSET_PTR) {                                        \
        conf = default;                                                      \
    }

#define ngx_conf_init_uint_value(conf, default)                              \
    if (conf == NGX_CONF_UNSET_UINT) {                                       \
        conf = default;                                                      \
    }

#define ngx_conf_init_size_value(conf, default)                              \
    if (conf == NGX_CONF_UNSET_SIZE) {                                       \
        conf = default;                                                      \
    }

#define ngx_conf_init_msec_value(conf, default)                              \
    if (conf == NGX_CONF_UNSET_MSEC) {                                       \
        conf = default;                                                      \
    }
// 合并函数宏，同样根据类型选择
#define ngx_conf_merge_value(conf, prev, default)                            \
    if (conf == NGX_CONF_UNSET) {                                            \
        conf = (prev == NGX_CONF_UNSET) ? default : prev;                    \
    }

#define ngx_conf_merge_ptr_value(conf, prev, default)                        \
    if (conf == NGX_CONF_UNSET_PTR) {                                        \
        conf = (prev == NGX_CONF_UNSET_PTR) ? default : prev;                \
    }

#define ngx_conf_merge_uint_value(conf, prev, default)                       \
    if (conf == NGX_CONF_UNSET_UINT) {                                       \
        conf = (prev == NGX_CONF_UNSET_UINT) ? default : prev;               \
    }

#define ngx_conf_merge_msec_value(conf, prev, default)                       \
    if (conf == NGX_CONF_UNSET_MSEC) {                                       \
        conf = (prev == NGX_CONF_UNSET_MSEC) ? default : prev;               \
    }

#define ngx_conf_merge_sec_value(conf, prev, default)                        \
    if (conf == NGX_CONF_UNSET) {                                            \
        conf = (prev == NGX_CONF_UNSET) ? default : prev;                    \
    }

#define ngx_conf_merge_size_value(conf, prev, default)                       \
    if (conf == NGX_CONF_UNSET_SIZE) {                                       \
        conf = (prev == NGX_CONF_UNSET_SIZE) ? default : prev;               \
    }

#define ngx_conf_merge_off_value(conf, prev, default)                        \
    if (conf == NGX_CONF_UNSET) {                                            \
        conf = (prev == NGX_CONF_UNSET) ? default : prev;                    \
    }
// 字符串的合并比较特殊，要检查空指针
#define ngx_conf_merge_str_value(conf, prev, default)                        \
    if (conf.data == NULL) {                                                 \
        if (prev.data) {                                                     \
            conf.len = prev.len;                                             \
            conf.data = prev.data;                                           \
        } else {                                                             \
            conf.len = sizeof(default) - 1;                                  \
            conf.data = (u_char *) default;                                  \
        }                                                                    \
    }

#define ngx_conf_merge_bufs_value(conf, prev, default_num, default_size)     \
    if (conf.num == 0) {                                                     \
        if (prev.num) {                                                      \
            conf.num = prev.num;                                             \
            conf.size = prev.size;                                           \
        } else {                                                             \
            conf.num = default_num;                                          \
            conf.size = default_size;                                        \
        }                                                                    \
    }

#define ngx_conf_merge_bitmask_value(conf, prev, default)                    \
    if (conf == 0) {                                                         \
        conf = (prev == 0) ? default : prev;                                 \
    }

// 解析-g传递的命令行参数
char *ngx_conf_param(ngx_conf_t *cf);

// 解析配置，参数filename可以是空
char *ngx_conf_parse(ngx_conf_t *cf, ngx_str_t *filename);
char *ngx_conf_include(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);

// 决定使用conf_prefix还是prefix得到完整文件名, 如果不是以“/”开始的绝对路径，就加上前缀/usr/local/nginx/conf
ngx_int_t ngx_conf_full_name(ngx_cycle_t *cycle, ngx_str_t *name,
    ngx_uint_t conf_prefix);

// 加入到cycle->open_files链表里,没有打开文件，之后在init_cycle里统一打开
ngx_open_file_t *ngx_conf_open_file(ngx_cycle_t *cycle, ngx_str_t *name);
void ngx_cdecl ngx_conf_log_error(ngx_uint_t level, ngx_conf_t *cf,
    ngx_err_t err, const char *fmt, ...);

// 预设的解析指令函数，可以解析bool/字符串/数字/秒等,命名格式是ngx_conf_set_xxx_slot
char *ngx_conf_set_flag_slot(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
char *ngx_conf_set_str_slot(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
char *ngx_conf_set_str_array_slot(ngx_conf_t *cf, ngx_command_t *cmd,
    void *conf);
char *ngx_conf_set_keyval_slot(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
char *ngx_conf_set_num_slot(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
char *ngx_conf_set_size_slot(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
char *ngx_conf_set_off_slot(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
char *ngx_conf_set_msec_slot(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
char *ngx_conf_set_sec_slot(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
char *ngx_conf_set_bufs_slot(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
char *ngx_conf_set_enum_slot(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
char *ngx_conf_set_bitmask_slot(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);


#endif /* _NGX_CONF_FILE_H_INCLUDED_ */
