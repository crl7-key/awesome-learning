
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#ifndef _NGX_SLAB_H_INCLUDED_
#define _NGX_SLAB_H_INCLUDED_


#include <ngx_config.h>
#include <ngx_core.h>


typedef struct ngx_slab_page_s  ngx_slab_page_t;

// slab内存页链表结构体
struct ngx_slab_page_s {
    uintptr_t         slab;
    ngx_slab_page_t  *next;
    uintptr_t         prev;
};


typedef struct {
    ngx_uint_t        total;
    ngx_uint_t        used;

    ngx_uint_t        reqs;
    ngx_uint_t        fails;
} ngx_slab_stat_t;


typedef struct {
    ngx_shmtx_sh_t    lock;

    size_t            min_size;
    size_t            min_shift;

    ngx_slab_page_t  *pages;  // 指向page数组的第一个成员page[0]的地址
    ngx_slab_page_t  *last;
    ngx_slab_page_t   free;  // 注意它是一个变量,free.next指向一个空闲的page[?]

    ngx_slab_stat_t  *stats; // 真正内存页的开始地址,每个内存页默认4K字节  
    ngx_uint_t        pfree;

    u_char           *start;
    u_char           *end;

    ngx_shmtx_t       mutex;

    u_char           *log_ctx;
    u_char            zero;

    unsigned          log_nomem:1;

    void             *data;
    void             *addr;
} ngx_slab_pool_t;


// slab内存页面大小初始化
void ngx_slab_sizes_init(void);

// 初始化slab结构,按slot和page管理这块共享内存,best-fit,之前需要初始化min_shift和end
// 自己使用可以把min_shift适当调整改大一点,分析以64位系统,4m共享内存为例,缺一个reinit函数,简单地清空共享内存
void ngx_slab_init(ngx_slab_pool_t *pool);

// 加锁分配内存
void *ngx_slab_alloc(ngx_slab_pool_t *pool, size_t size);

// 不加锁分配内存,超过2k则直接分配整页
void *ngx_slab_alloc_locked(ngx_slab_pool_t *pool, size_t size);

// 加锁分配内存并清空
void *ngx_slab_calloc(ngx_slab_pool_t *pool, size_t size);

// 不加锁分配内存并清空
void *ngx_slab_calloc_locked(ngx_slab_pool_t *pool, size_t size);

// 加锁释放内存
void ngx_slab_free(ngx_slab_pool_t *pool, void *p);

// 不加锁分配内存
void ngx_slab_free_locked(ngx_slab_pool_t *pool, void *p);


#endif /* _NGX_SLAB_H_INCLUDED_ */
