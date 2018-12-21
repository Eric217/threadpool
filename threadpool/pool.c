//
//  pool.c
//  Para
//
//  Created by Eric on 2018/12/18.
//  Copyright © 2018 Eric. All rights reserved.
//

#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

#include "pool.h"
#include "debug.h"


void* thread_routine(void* _pool) {
    thread_pool_t* pool = (thread_pool_t*)_pool;
    pthread_t tid = pthread_self();
    
    PRINT("Thread %#lx starting\n", (size_t)tid);

    int timedout;
    
    while (1) {
        timedout = 0;
        cond_lock(&pool->ready);
        pool->idle++;
        //
        while (pool->first == 0 && pool->quit == 0) {
            PRINT("Thread %#lx waiting\n", (size_t)tid);
            struct timeval tv;
            struct timespec ts;
            gettimeofday(&tv, 0);
            ts.tv_sec = tv.tv_sec + 2;
            ts.tv_nsec = 0;
            int ret = condition_timedwait(&pool->ready, &ts);
            if (ret == ETIMEDOUT) {
                PRINT("Thread %#lx waiting timedout\n", (size_t)tid);
                timedout = 1;
                break;
            }
        }
        pool->idle--;
        if (pool->first) {
            task_t* tk = pool->first;
            pool->first = tk->next;
            cond_unlock(&pool->ready);
            tk->function(tk->args);
            free(tk);
            cond_lock(&pool->ready);
        }
        
        if (pool->quit && pool->first == 0) {
            pool->thread_count--;
            if (pool->thread_count == 0) {
                cond_signal(&pool->ready);
            }
            cond_unlock(&pool->ready);
            break;
        }
        
        if (timedout && pool->first == 0) {
            pool->thread_count--;
            cond_unlock(&pool->ready);
            break;
        }
        
        cond_unlock(&pool->ready);

    }
    PRINT("Thread %#lx exiting\n", (size_t)tid);

    return 0;
}

//initialize thread pool
void thread_pool_init(thread_pool_t* pool, int max_threads) {
    cond_init(&pool->ready);
    pool->first = pool->last = 0;
    pool->quit = pool->thread_count = pool->idle = 0;
    pool->max_thread_count = max_threads;
    PRINT("线程池大小：%d \n", max_threads);
}

//deallocate thread pool
void thread_pool_destroy(thread_pool_t *pool) {
    if (pool->quit) {
        return;
    }
    
    cond_lock(&pool->ready);
    
    pool->quit = 1;
    if(pool->thread_count) {
        //the working thread cannot receive the broadcast notification
        if(pool->idle)
            cond_broadcast(&pool->ready);
        
        while(pool->thread_count) {
            //printf("Waiting thread(s) to exit\n");
            cond_wait(&pool->ready);
        }
    }
    
    cond_unlock(&pool->ready);
    cond_destroy(&pool->ready);
}

// add a task to thread pool
void thread_pool_add_task(thread_pool_t *pool, func task, args arg) {
    task_t* newtask = (task_t*)malloc(sizeof(task_t));
    newtask->function = task;
    newtask->args = arg;
    newtask->next = 0;
    
    cond_lock(&pool->ready);
    
    // insert newtask at the end of the queue
    if(pool->first) {
        pool->last->next = newtask;
    } else {
        pool->first = newtask;
    }
    pool->last = newtask;
    
    // notify waiting threads
    if(pool->idle > 0) {
        cond_signal(&pool->ready);
    } else if(pool->thread_count < pool->max_thread_count) {
        // add new thread if not reaching limit
        pthread_t tid;
        int ret = pthread_create(&tid, 0, thread_routine, (void*)pool);
        ASSERT(ret == 0);
        pool->thread_count++;
    }
    
    cond_unlock(&pool->ready);
}

// void* test(void* arg) {
//     printf("task %d is preparing...\n", *(int*)arg);
//     sleep(1);
//     printf("task %d is printed\n", *(int*)arg);
//     return 0;
// }

// int main() {
//     thread_pool_t pool;
//     thread_pool_init(&pool, 3);
//     printf("core of %d started\n", 3);
//     int a[10];
//     for (int i = 0; i < 10; i++) {
//         a[i] = i;
//         thread_pool_add_task(&pool, test, a+i);
//     }
//     printf("process will end -------------- \n");
//     thread_pool_destroy(&pool);
//     printf("process did end\n");
//     return 0;
// }
