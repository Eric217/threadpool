//
//  pool.h
//  Para
//
//  Created by Eric on 2018/12/18.
//  Copyright © 2018 Eric. All rights reserved.
//

#ifndef pool_h
#define pool_h

#include <stdio.h>

#include "condition.h"

typedef void* (*func) (void*);
typedef void* args;

typedef struct task {
    func function;
    args args;
    struct task* next;
} task_t;


typedef struct thread_pool {
    condition_t ready;
    task_t* first;
    task_t* last;
    int thread_count;
    int idle;
    int max_thread_count;
    int quit;
     
} thread_pool_t;


void thread_pool_init(thread_pool_t*, int max_threads);

void thread_pool_destroy(thread_pool_t *);

void thread_pool_add_task(thread_pool_t *, func function, void* args);


 
#endif /* pool_h */
