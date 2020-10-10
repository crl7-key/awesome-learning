
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#ifndef _NGX_PALLOC_H_INCLUDED_
#define _NGX_PALLOC_H_INCLUDED_


#include <ngx_config.h>
#include <ngx_core.h>


/*
 * NGX_MAX_ALLOC_FROM_POOL should be (ngx_pagesize - 1), i.e. 4095 on x86.
 * On Windows NT it decreases a number of locked pages in a kernel.
 */
#define NGX_MAX_ALLOC_FROM_POOL  (ngx_pagesize - 1)

// 默认线程池大小
#define NGX_DEFAULT_POOL_SIZE    (16 * 1024)

#define NGX_POOL_ALIGNMENT       16
#define NGX_MIN_POOL_SIZE                                                     \
    ngx_align((sizeof(ngx_pool_t) + 2 * sizeof(ngx_pool_large_t)),            \
              NGX_POOL_ALIGNMENT)


typedef void (*ngx_pool_cleanup_pt)(void *data);

typedef struct ngx_pool_cleanup_s  ngx_pool_cleanup_t;

// 清理回调的数据结构
struct ngx_pool_cleanup_s {
    
    // 清理的回调函数, 当前 cleanup 数据的回调函数  ngx_destroy_pool中执行   例如清理文件句柄ngx_pool_cleanup_file等
    ngx_pool_cleanup_pt   handler;
    
    // 指向存储的数据地址,内存的真正地址 
    void                 *data;
    
    // 下一个ngx_pool_cleanup_t内存的指针
    ngx_pool_cleanup_t   *next;
};
/**
 *   内存池           ---  ngx_pool_s;
 *   内存块数据       ---  ngx_pool_data_t;
 *   大内存块         --- ngx_pool_large_s; 
 **/

typedef struct ngx_pool_large_s  ngx_pool_large_t;

// ngx_pool_large_s 大内存块,链表
struct ngx_pool_large_s {
    
    // 指向下一个存储地址 通过这个地址可以知道当前块长度
    ngx_pool_large_t     *next;
    
    // 数据块指针地址,即申请的内存块地址   
    void                 *alloc;
};

// ngx_pool_data_t 内存块数据
typedef struct {
    
    // 内存池中未使用内存的开始节点地址
    u_char               *last;
    
    //  内存池的结束地址
    u_char               *end;
    
    // 指向下一个内存池
    ngx_pool_t           *next;
    
    // 失败次数
    ngx_uint_t            failed;
} ngx_pool_data_t;


//  Nginx 内存池数据结构
struct ngx_pool_s {
    
    // 内存池的数据区域
    ngx_pool_data_t       d;  
    
    // 最大每次可分配内存
    size_t                max;
    
    // 指向当前的内存池指针地址. ngx_pool_t链表上最后一个缓存池结构
    ngx_pool_t           *current;
    
    // 缓冲区链表
    ngx_chain_t          *chain;
    
    // 存储大数据的链表
    ngx_pool_large_t     *large;
    
    // 可自定义回调函数,清除内存块分配的内存
    ngx_pool_cleanup_t   *cleanup;
    
    // 日志日志对象
    ngx_log_t            *log;
};


typedef struct {
    // 文件描述符
    ngx_fd_t              fd;
    
    //文件名称
    u_char               *name;
    
    // 日志对象
    ngx_log_t            *log;
} ngx_pool_cleanup_file_t;


// 创建线程池,一开始只有一个内存池节点
ngx_pool_t *ngx_create_pool(size_t size, ngx_log_t *log);

// 销毁内存池, 调用清理函数链表,检查大块内存链表，直接free, 遍历内存池节点,逐个free
void ngx_destroy_pool(ngx_pool_t *pool);

// 重置内存池,释放内存,但没有free归还给系统,之前已经分配的内存块仍然保留,遍历内存池节点,逐个重置空闲指针位置
// 注意cleanup链表没有清空,只有destroy时才会销毁
void ngx_reset_pool(ngx_pool_t *pool);

// 分配对齐的内存,速度快,可能有少量浪费,多用于创建结构体
void *ngx_palloc(ngx_pool_t *pool, size_t size);

// 分配未对齐的内存,多用于字符串等不规则内存需求
void *ngx_pnalloc(ngx_pool_t *pool, size_t size);

// 使用ngx_palloc分配内存,并将内存块清零
void *ngx_pcalloc(ngx_pool_t *pool, size_t size);

// 字节对齐分配大块内存
void *ngx_pmemalign(ngx_pool_t *pool, size_t size, size_t alignment);

// 把内存归还给内存池,通常无需调用, 实际上只释放大块内存
ngx_int_t ngx_pfree(ngx_pool_t *pool, void *p);


// 创建一个清理结构体,size是ngx_pool_cleanup_t::data分配的大小
// size可以为0,用户需要自己设置ngx_pool_cleanup_t::data指针
ngx_pool_cleanup_t *ngx_pool_cleanup_add(ngx_pool_t *p, size_t size);

// 清除 p->cleanup链表上的内存块(主要是文件描述符) 回调函数：ngx_pool_cleanup_file
void ngx_pool_run_cleanup_file(ngx_pool_t *p, ngx_fd_t fd);

// 关闭文件回调函数 ngx_pool_run_cleanup_file方法执行的时候,用了此函数作为回调函数的,都会被清理
void ngx_pool_cleanup_file(void *data);

// 删除文件回调函数
void ngx_pool_delete_file(void *data);


#endif /* _NGX_PALLOC_H_INCLUDED_ */
