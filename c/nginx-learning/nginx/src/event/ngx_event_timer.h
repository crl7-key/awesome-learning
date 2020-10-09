
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#ifndef _NGX_EVENT_TIMER_H_INCLUDED_
#define _NGX_EVENT_TIMER_H_INCLUDED_


#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_event.h>


#define NGX_TIMER_INFINITE  (ngx_msec_t) -1

#define NGX_TIMER_LAZY_DELAY  300

// 初始化定时器,实际上就是初始化一个红黑树结构, 注意树的插入函数是ngx_rbtree_insert_timer_value
ngx_int_t ngx_event_timer_init(ngx_log_t *log);

// 在红黑树里查找最小值,即最左边的节点,得到超时的时间差值
// 如果时间已经超过了,那么时间差值就是0,意味着在红黑树里已经有事件超时了，必须立即处理
//
// timer > 0  红黑树里即将超时的事件的时间
// timer < 0  表示红黑树为空，即无超时事件
// timer == 0 意味着在红黑树里已经有事件超时了,必须立即处理
// timer == 0 epoll就不会等待,收集完事件立即返回
ngx_msec_t ngx_event_find_timer(void);

// 遍历定时器红黑树,找出所有过期的事件,调用handler处理超时
void ngx_event_expire_timers(void);

// 检查红黑树里是否还有定时器
ngx_int_t ngx_event_no_timers_left(void);

extern ngx_rbtree_t  ngx_event_timer_rbtree;

// 删除定时器 
static ngx_inline void
ngx_event_del_timer(ngx_event_t *ev)
{
    ngx_log_debug2(NGX_LOG_DEBUG_EVENT, ev->log, 0,
                   "event timer del: %d: %M",
                    ngx_event_ident(ev->data), ev->timer.key);

    ngx_rbtree_delete(&ngx_event_timer_rbtree, &ev->timer);

#if (NGX_DEBUG)
    ev->timer.left = NULL;
    ev->timer.right = NULL;
    ev->timer.parent = NULL;
#endif

    ev->timer_set = 0;
}

// 添加定时器
static ngx_inline void
ngx_event_add_timer(ngx_event_t *ev, ngx_msec_t timer)
{
    ngx_msec_t      key;
    ngx_msec_int_t  diff;

    key = ngx_current_msec + timer;

    if (ev->timer_set) { //如果之前该ev已经添加过，则先把之前的ev定时器del掉，然后在重新添加

        /*
         * Use a previous timer value if difference between it and a new
         * value is less than NGX_TIMER_LAZY_DELAY milliseconds: this allows
         * to minimize the rbtree operations for fast connections.
         */

        diff = (ngx_msec_int_t) (key - ev->timer.key);

        if (ngx_abs(diff) < NGX_TIMER_LAZY_DELAY) {
            ngx_log_debug3(NGX_LOG_DEBUG_EVENT, ev->log, 0,
                           "event timer: %d, old: %M, new: %M",
                            ngx_event_ident(ev->data), ev->timer.key, key);
            return;
        }

        ngx_del_timer(ev);
    }

    ev->timer.key = key;

    ngx_log_debug3(NGX_LOG_DEBUG_EVENT, ev->log, 0,
                   "event timer add: %d: %M:%M",
                    ngx_event_ident(ev->data), timer, ev->timer.key);

    // 上树
    ngx_rbtree_insert(&ngx_event_timer_rbtree, &ev->timer);

    ev->timer_set = 1;
}


#endif /* _NGX_EVENT_TIMER_H_INCLUDED_ */
